/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME               : GasContainer2D.h
 * FILE AUTHORS            : Daniil Martsenyuk, Serkov Alexander (co-author).
 * PURPOSE                 : test 2-dimensional gas class
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include "../Simulator.h"
#include "GasCell.h"

namespace unreal_fluid::physics::gas {
  class GasContainer2d : public IPhysicalObject {
    int _height;
    int _width;
    std::vector<std::vector<GasCell>> _storage;
    std::vector<std::vector<double>> _flowsX;
    std::vector<std::vector<double>> _flowsY;

  public:
    /// @brief Constructor.
    /// @param height height of container
    /// @param width width of container
    /// @param particle_number amount of particles in container (randomly distributed)
    GasContainer2d(int height, int width, int particle_number);

  private:
    /// @brief Calculate flow between two cells.
    /// @param cell1 first cell (potential source)
    /// @param cell2 second cell (potential target)
    [[nodiscard]] double calculateFlow(const GasCell &cell1, const GasCell &cell2) const;
    /// @brief Calculate flow between two cells and save it in cells.
    /// @param cell1, cell2 cells
    /// @param x, y - position
    void calculateAndSaveFlow(GasCell &cell1, GasCell &cell2, int x, int y, bool isHorizontal);
    /// @brief Calculate all flows in container.
    /// @param dt time step
    void calculateFlows(double dt);

    /// @brief Apply flow between two cells.
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

// end of GasContainer2D.h