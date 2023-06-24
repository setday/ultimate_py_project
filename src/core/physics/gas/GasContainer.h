/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : GasContainer.h
 * PURPOSE   : base gas implementation
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../Simulator.h"
#include "GasCell.h"

namespace unreal_fluid::physics::gas {
  class GasContainer : public IPhysicalObject {
    int _height;
    int _width;
    int _depth;
    std::vector<std::vector<std::vector<GasCell>>> _storage;
    std::vector<std::vector<std::vector<double>>> _flowsX;
    std::vector<std::vector<std::vector<double>>> _flowsY;
    std::vector<std::vector<std::vector<double>>> _flowsZ;

  public:
    GasContainer(int height, int width, int depth, int particle_number);

  private:
    /// @brief Calculate targetFlow between two cells.
    /// @param cell1 first cell (potential source)
    /// @param cell2 second cell (potential target)
    /// @param dt time step
    [[nodiscard]] double calculateFlow(const GasCell &cell1, const GasCell &cell2, double dt) const;
    /// @brief Calculate targetFlow between two cells and save it in cells.
    /// @param cell1, cell2 cells
    /// @param x, y, z - position
    /// @param dt time step
    /// @param type 0 if OX, 1 if OY, 2 if OZ
    void calculateAndSaveFlow(GasCell &cell1, GasCell &cell2, int x, int y, int z, int type, double dt);
    /// @brief Calculate all flows in container.
    /// @param dt time step
    void calculateFlows(double dt);

    /// @brief Apply targetFlow between two cells.
    /// @param cell1 first cell
    /// @param cell2 second cell
    void applyFlow(GasCell &cell1, GasCell &cell2, double targetFlow) const;
    /// @brief Move flows in container.
    /// @param dt time step
    void applyFlows(double dt);

    /// @brief Diffuse gas between two cells.
    /// @param cell1 first cell
    /// @param cell2 second cell
    void diffuseTwoCells(GasCell &cell1, GasCell &cell2, double dt);
    /// @brief Diffuse gas in container.
    void diffuseCells(double dt);

    /// @brief Dissolve gas in cell.
    /// @param cell cell to dissolve
    /// @param dt time step
    void dissolveCell(GasCell &cell, double dt);
    /// @brief Dissolve gas in container.
    /// @param dt time step
    void dissolveCells(double dt);

    void advect(double dt);

  public:
    /* abstract class implementation */

    [[nodiscard]] Type getType() override;
    [[nodiscard]] void *getData() override;

  private:
    /// @brief Simulate gas container.
    /// @param dt time step
    void simulate(double dt) override;
  };
} // namespace unreal_fluid::physics::gas

// end of GasContainer.h