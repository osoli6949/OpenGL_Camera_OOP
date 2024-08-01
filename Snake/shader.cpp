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
  this->programAddress = glCreateProgram();
  int success;
  char infoLog[512];
  glAttachShader(this->programAddress, this->vertexShader);
  glAttachShader(this->programAddress, this->fragmentShader);
  glLinkProgram(this->programAddress);

  glGetProgramiv(this->programAddress, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(this->programAddress, 512, NULL, infoLog);
    throw runtime_error(string("ERROR::PROGRAM::COMPILATION_FAILED\n") +
                        infoLog);
  }
}

void ShaderProgram::setUniform1i(const std::string& name, int value) const {
  glUniform1i(glGetUniformLocation(this->programAddress, name.c_str()), value);
}

void ShaderProgram::setUniform4f(const std::string& name,
                                 glm::vec4 value) const {
  glUniform4f(glGetUniformLocation(this->programAddress, name.c_str()),
              value[0], value[1], value[2], value[3]);
}

void ShaderProgram::setUniformMatrix4fv(const std::string& name,
                                        glm::mat4 value) const {
  glUniformMatrix4fv(glGetUniformLocation(this->programAddress, name.c_str()),
                     1, GL_FALSE, value_ptr(value));
}