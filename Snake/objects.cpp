#include "objects.h"
using std::vector, std::move;

VBO::VBO(vector<float> vertices) : vertices{move(vertices)} {
  glGenBuffers(1, &this->VBOAdress);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBOAdress);
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float),
               &this->vertices[0], GL_STATIC_DRAW);
}

void VBO::vertexAttrib(int location, int size, size_t stride, size_t offset) {
  glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE,
                        stride * sizeof(float),
                        (void*)(offset * sizeof(float)));
  glEnableVertexAttribArray(location);
}

VAO::VAO() {
  glGenVertexArrays(1, &this->VAOAdress);
  glBindVertexArray(this->VAOAdress);
}

EBO::EBO(vector<unsigned int> indices) : indices{move(indices)} {
  glGenBuffers(1, &this->EBOAdress);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBOAdress);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               this->indices.size() * sizeof(unsigned int), &this->indices[0],
               GL_STATIC_DRAW);
}

void EBO::draw(GLenum mode, int count, int offset) {
  glDrawElements(mode, count, GL_UNSIGNED_INT,
                 (void*)(offset * sizeof(unsigned int)));
}