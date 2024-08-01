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
  void setUniform1i(const std::string& name, int value) const;
  void setUniform4f(const std::string& name, glm::vec4 value) const;
  void setUniformMatrix4fv(const std::string& name, glm::mat4 value) const;
};

#endif