#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stdexcept>
#include <string>

#include "stb_image.h"

class Window {
 protected:
  GLFWwindow* window;
  int width, height;

 public:
  Window(int, int, const char*);
  ~Window();

  void processInput();
  virtual void renderLoop();

  // callbacks
  void framebuffer_size_callback();
};

#endif