#ifndef OBJECTS_H
#define OBJECTS_H

#include <utility>
#include <vector>

#include "window.h"

class VBO  // Vertex Buffer Object
{
  unsigned int VBOAdress;
  std::vector<float> vertices;

 public:
  VBO(std::vector<float> vertices);
  void bind() const { glBindBuffer(GL_ARRAY_BUFFER, this->VBOAdress); }
  void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
  void vertexAttrib(int location, int size, size_t stride, size_t offset);
};

class VAO  // Vertex Array Object
{
  unsigned int VAOAdress;

 public:
  VAO();
  void draw(GLenum mode, int from, int to) { glDrawArrays(mode, from, to); }
  void bind() const { glBindVertexArray(this->VAOAdress); }
  void unbind() const { glBindVertexArray(0); }
};

class EBO  // Element Buffer Object
{
  unsigned int EBOAdress;
  std::vector<unsigned int> indices;

 public:
  EBO(std::vector<unsigned int> indices);
  void draw(GLenum mode, int count, int offset);
  void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBOAdress); }
  void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
};

#endif