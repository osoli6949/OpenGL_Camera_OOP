#ifndef SHADER_H
#define SHADER_H

#include "window.h"

class Shader {
  const char* shaderSource;
  unsigned int shaderAddress;

 public:
  Shader(GLenum shaderType, std::string shaderLocation);
  unsigned int getAddress() { return this->shaderAddress; }
};

class ShaderProgram {
  unsigned int programAddress;
  unsigned int vertexShader;
  unsigned int fragmentShader;

 public:
  ShaderProgram(unsigned int vertex, unsigned int frag);
  ~ShaderProgram() {
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
  }
  void use() const { glUseProgram(this->programAddress); }
};

#endif