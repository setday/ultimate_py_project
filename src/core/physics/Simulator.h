//
// Created by User on 3/17/2023.
//

#pragma once
#include "vector"
#include "PhysObject.h"

namespace unreal_fluid::physics{
    class Simulator {
    private:
        std::vector<PhysObject*> physObjects;
    public:
        Simulator() = default;
        ~Simulator() = default;

        /// @brief Adds PhysObject to scene
        /// @details Adds PhysObject into an internal buffer.
        /// Call simulate() to simulate all of the PhysObjects in the buffer
        void addPhysObject(PhysObject* physObject);

        /// @brief Simulates the scene
        /// @details calls simulate() function of each PhysObject in the internal buffer and solve interactions between them.
        void simulate(double dt);

        /// @brief Clears the scene
        /// @details after this function is called, the internal buffer is absolutely empty. No
        void clearData();
    };
}

