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

#include "baked_mesh/BakedMesh.h"
#include "material/BasicMaterial.h"
#include "../../managers/sub_programs_managers/shader_manager/ShaderManager.h"

namespace unreal_fluid::render {
  class RenderObject {
  public:
    mat4 modelMatrix = mat4();

    std::shared_ptr<mesh::BakedMesh> bakedMesh;
    material::BasicMaterial material;
    const ShaderProgram *shaderProgram = render::DefaultShaderManager::GetDefaultProgram();

    int isEmitter = 0; /// TODO: remove this field

    RenderObject() = default;
    ~RenderObject() = default;

    /// Load render object from file.
    /// @param path Path to file.
    /// @attention Only .obj files are supported.
    void loadFromFile(std::string_view path);

    /// Bind parameters to shader program.
    /// @param shader Shader program.
    void bindParametersToShader(const ShaderProgram *shader) const;

  private:
    /// Load render object from .obj file.
    /// @param file File to load.
    /// @return True if success, false otherwise.
    bool loadFromObjFile(std::ifstream &file);
  };
} // namespace unreal_fluid::render

// end of renderObject.h
