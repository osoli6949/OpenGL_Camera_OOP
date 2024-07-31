#include "shader.h"

using std::runtime_error, std::string, std::ifstream;

Shader::Shader(GLenum shaderType, string shaderLocation) {
  string line, text;
  ifstream in(shaderLocation);
  while (getline(in, line)) text += line + "\n";
  this->shaderSource = text.c_str();

  int success;
  char infoLog[512];

  this->shaderAddress = glCreateShader(shaderType);
  glShaderSource(this->shaderAddress, 1, &this->shaderSource, NULL);
  glCompileShader(this->shaderAddress);

  glGetShaderiv(this->shaderAddress, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(this->shaderAddress, 512, NULL, infoLog);
    throw runtime_error(string("ERROR::SHADER::COMPILATION_FAILED\n") +
                        infoLog);
  }
}

ShaderProgram::ShaderProgram(unsigned int vertex, unsigned int frag)
    : vertexShader(vertex), fragmentShader(frag) {
  int success;
  char infoLog[512];
  glAttachShader(this->programAddress, this->vertexShader);
  glAttachShader(this->programAddress, this->fragmentShader);
  glLinkProgram(this->programAddress);

  glGetProgramiv(this->programAddress, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(this->programAddress, 512, NULL, infoLog);
    throw runtime_error(string("ERROR::PROGRAM::COMPILATION_FAILED\n") +
                        infoLog);
  }
}