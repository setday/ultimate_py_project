/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : renderObject.h
 * PURPOSE   : Class that realizes render object.
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <vector>
#include "../../managers/sub_programs_managers/shader_manager/ShaderManager.h"
#include "material/BasicMaterial.h"
#include "mesh/BasicMesh.h"

namespace unreal_fluid::render {
  class RenderObject {
  public:
    mat4 modelMatrix = mat4();

    mesh::BasicMesh mesh;
    material::BasicMaterial material;
    const ShaderProgram *shaderProgram = render::DefaultShaderManager::GetDefaultProgram();

    RenderObject() = default;
    ~RenderObject() = default;

    /// Load render object from file.
    /// @param path Path to file.
    /// @attention Only .obj files are supported.
    void loadFromFile(std::string_view path);

  private:
    /// Load render object from .obj file.
    /// @param file File to load.
    /// @return True if success, false otherwise.
    bool loadFromObjFile(std::ifstream &file);
  };
} // namespace unreal_fluid::render

// end of renderObject.h
