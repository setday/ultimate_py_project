/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : BakedMesh.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "BakedMesh.h"

using namespace unreal_fluid::render::mesh;

BakedMesh::BakedMesh(BasicMesh *basicMesh, Type type) : _indicesCount(basicMesh->indices.size()),
                                                        _type(type), mesh(basicMesh) {
  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);

  glGenBuffers(1, &_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texCoord));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glGenBuffers(1, &_ibo);

  updateBufferedMesh();
}

BakedMesh::~BakedMesh() {
  glDeleteBuffers(1, &_vbo);
  glDeleteBuffers(1, &_ibo);
  glDeleteVertexArrays(1, &_vao);
}

void BakedMesh::updateBufferedMesh() {
  std::vector<Vertex> const &vertices = mesh->vertices;
  std::vector<unsigned int> const &indices = mesh->indices;

  _indicesCount = indices.size();

  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(),
               _type == Type::STATIC ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(),
               _type == Type::STATIC ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint BakedMesh::getVAO() const {
  return _vao;
}

GLuint BakedMesh::getVBO() const {
  return _vbo;
}

GLuint BakedMesh::getIBO() const {
  return _ibo;
}

size_t BakedMesh::getIndicesCount() const {
  return _indicesCount;
}

// end of BakedMesh.cxx
