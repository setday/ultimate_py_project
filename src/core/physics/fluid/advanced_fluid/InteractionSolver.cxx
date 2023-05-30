/***************************************************************
* Copyright (C) 2023
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT   : ultimate_py_project
* AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
* FILE NAME : InteractionSolver.cxx
* PURPOSE   : solve interactions
*
* No part of this file may be changed and used without agreement of
* authors of this project.
*/

#include "InteractionSolver.h"

using namespace unreal_fluid::physics::fluid;
using unreal_fluid::physics::CollisionSolver;

unreal_fluid::physics::fluid::InteractionSolver::InteractionSolver() {
  coreNumber = std::thread::hardware_concurrency();
  assert(coreNumber > 0);
  distributors.resize(coreNumber);
}

void task(CellsDistributor &distributor, std::vector<Particle *> &particles, double k, bool *ready) {
  //CellsDistributor distributor;
  distributor.update(particles);
  for (auto &bigParticle: distributor.big_particles) {
    for (auto &particle: particles) {
      if ((particle->position - bigParticle->position).len() <= particle->radius + bigParticle->radius)
        CollisionSolver::particleWithParticleCollision(particle, bigParticle, k);
    }
  }
  for (auto p = distributor.nextPair(); p != CellsDistributor::terminator; p = distributor.nextPair())
    CollisionSolver::particleWithParticleCollision(p.first, p.second, k);
  *ready = true;
}

void InteractionSolver::interact(std::vector<Particle *> &particles, double k) {
  if (particles.size() > 100) {
    std::vector<std::vector<Particle *>> subParticles(coreNumber);
    std::vector<bool *> threadsFinished(coreNumber);
    for (int i = 0; i < threadsFinished.size(); ++i) {
      threadsFinished[i] = new bool;
      *threadsFinished[i] = false;
    }
    for (int i = 0; i < coreNumber; ++i) {
      size_t beginIndex = i * particles.size() / coreNumber;
      size_t endIndex = (i + 1) * particles.size() / coreNumber;
      endIndex = std::min(endIndex, particles.size());
      for (int j = beginIndex; j < endIndex; ++j) {
        subParticles[i].push_back(particles[j]);
      }
    }

    //LOG_INFO("Detaching");
    for (int i = 0; i < coreNumber; ++i) {
      bool *ready = threadsFinished[i];
      interactionTasks.emplace_back(task, std::ref(distributors[i]), std::ref(subParticles[i]), k, ready);
      interactionTasks.back().detach();
    }

    //LOG_INFO("Started");
    while (true) {
      bool everybodyFinished = true;
      for (int i = 0; i < coreNumber; ++i) {
        everybodyFinished &= *threadsFinished[i];
      }
      if (everybodyFinished) {
        break;
      }
    }
    //LOG_INFO("Joined");
  } else {
    bool *ready = new bool;
    *ready = false;
    task(distributors[0], particles, k, ready);
  }
}
