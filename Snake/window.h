#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
// glad should always be included before GLFW
#include <GLFW/glfw3.h>

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stdexcept>
#include <string>

class Window {
 protected:
  GLFWwindow* window;
  int width, height;  // window size

 public:
  Window(int width, int height, const char* title);
  ~Window();
  GLFWwindow* getWindow() { return this->window; }

  virtual void processInput(float deltaTime);
  int shouldClose();
  void swapBuffers();
  void backgroundColor(glm::vec4 color);

  // callbacks
  void framebuffer_size_callback() const;
};

#endif