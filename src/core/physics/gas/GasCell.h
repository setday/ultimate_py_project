/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME               : GasCell.h
 * FILE AUTHORS            : Daniil Martsenyuk, Serkov Alexander (co-author).
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include "../../../Definitions.h"

namespace unreal_fluid::physics::gas {
  class GasCell {
  public:
    double amountOfGas = 0;  // = mass / molarMass
    double volume = 1;        // volume of cell (now 1x1x1)
    double temperature = 300; // temperature of gas
    double targetFlow = 0;
    double particlesFlow = 0;
    vec3f color = {1, 1, 1}; // color is a quantity to define gas

    GasCell() = default;
    explicit GasCell(double amountOfGas, vec3f color = {1, 1, 1}, double temperature = 300);

    /// @brief get pressure of gas cell
    [[nodiscard]] double getPressure() const;

    /// @brief slice gas cell
    /// @param particlesCount amount of gas to slice
    /// @return new gas cell with sliced gas
    GasCell slice(double particlesCount);
    /// @brief add gas cell to current
    /// @param cell gas cell to add
    void add(GasCell cell);
  }; // class GasCell
} // namespace unreal_fluid::physics::gas

// end of GasCell.h
