/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : renderObject.cxx
 * PURPOSE   : Class that realizes render object.
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include <sstream>

#include "RenderObject.h"

#define OBJECTS_PATH "../objects/"

using namespace unreal_fluid::render;

void RenderObject::loadFromFile(std::string_view path) {
  std::string realPath = std::string(OBJECTS_PATH) + path.data();
  std::ifstream file(realPath);

  if (!file.is_open()) {
    Logger::logError("Can't open file:", realPath);

    return;
  }

  std::string extension = path.data();
  extension = extension.substr(extension.find_last_of('.') + 1);

  if (extension != "obj") {
    Logger::logError("Can't load file", path, "with extension:", extension);

    return;
  } else {
    if (!loadFromObjFile(file))
      Logger::logError("Can't load file", path, "with extension:", extension);
  }
}

bool RenderObject::loadFromObjFile(std::ifstream &file) {
  std::vector<vec3f> positions;
  std::vector<vec3f> normals;
  std::vector<vec2f> texCoords;

  positions.emplace_back(0);
  normals.emplace_back(0);
  texCoords.emplace_back(0);

  std::string line;
  while (std::getline(file, line)) {
    std::stringstream lineStream(line);
    std::string lineType;

    lineStream >> lineType;

    if (lineType == "v") {
      vec3f position;
      lineStream >> position;
      positions.push_back(position);
    } else if (lineType == "vn") {
      vec3f normal;
      lineStream >> normal;
      normals.push_back(normal);
    } else if (lineType == "vt") {
      vec2f texCoord;
      lineStream >> texCoord;
      texCoords.push_back(texCoord);
    } else if (lineType == "f") {
      auto parseVertex = [](const std::string &vertex) {
        std::stringstream vertexStream(vertex);
        std::string vertexPart;
        std::vector<int> vertexParts;

        while (std::getline(vertexStream, vertexPart, '/')) {
          if (vertexPart.empty())
            vertexParts.push_back(0);
          else
            vertexParts.push_back(std::stoi(vertexPart));
        }

        return vertexParts;
      };

      int firstIndex = mesh.vertices.size();
      std::string vertex;
      while (lineStream >> vertex) {
        std::vector<int> vertexParts = parseVertex(vertex);

        mesh.vertices.emplace_back(
                positions[vertexParts[0]],
                normals[vertexParts[2]],
                texCoords[vertexParts[1]]
                );
      }

      int lastIndex = mesh.vertices.size() - 1;

      while (firstIndex < lastIndex) {
        mesh.indices.emplace_back(lastIndex--);
        mesh.indices.emplace_back(firstIndex++);
      }

      if (lastIndex == firstIndex) {
        mesh.indices.emplace_back(firstIndex);
      }

      mesh.indices.emplace_back(RESET_INDEX);
    }
  }

  file.close();

  return true;
}

// end of renderObject.cxx
