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

#include "stb_image.h"

class Window {
 protected:
  GLFWwindow* window;
  int width, height;

 public:
  Window(int width, int height, const char* title);
  ~Window();

  void processInput();
  int shouldClose();
  void swapBuffers();

  // callbacks
  void framebuffer_size_callback();
};

#endif