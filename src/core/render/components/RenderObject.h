/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : RenderObject.h
 * FILE AUTHORS            : Serkov Alexander.
 * PURPOSE                 : Class that realizes render object.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include <vector>

#include "baked_mesh/BakedMesh.h"
#include "material/BasicMaterial.h"
#include "texture/Texture.h"
#include "../../managers/sub_programs_managers/shader_manager/ShaderManager.h"

namespace unreal_fluid::render {
  class RenderObject {
  public:
    mat4 modelMatrix = mat4();

    std::shared_ptr<mesh::BakedMesh> bakedMesh;
    material::BasicMaterial material;
    Texture *textures[4];
    ShaderProgram *shaderProgram = render::DefaultShaderManager::GetDefaultProgram();

    int isEmitter = 0; /// TODO: remove this field

    /// Default constructor.
    RenderObject() = default;
    /// Load render object from file.
    /// @param path Path to file.
    /// @attention Only .obj files are supported.
    RenderObject(std::string_view path);
    ~RenderObject() = default;

    /// Load render object from file.
    /// @param path Path to file.
    /// @attention Only .obj files are supported.
    void loadFromFile(std::string_view path);

    /// Bind parameters to shader program.
    /// @param shader Shader program.
    void bindParametersToShader(ShaderProgram *shader) const;

  private:
    /// Load render object from .obj file.
    /// @param file File to loadFromFile.
    /// @return True if success, false otherwise.
    bool loadFromObjFile(std::ifstream &file);
  };
} // namespace unreal_fluid::render

// end of renderObject.h
