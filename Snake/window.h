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

  // cursor values
  double lastX, lastY;     // cursor position
  float xoffset, yoffset;  // cursor movement
  bool returned = false;

 public:
  Window(int width, int height, const char* title);
  ~Window();
  GLFWwindow* getWindow() { return this->window; }
  glm::vec2 getOffset();

  void processInput();
  int shouldClose();
  void swapBuffers();
  void backgroundColor(glm::vec4 color);

  // callbacks
  void framebuffer_size_callback() const;
  void mouse_callback(double xpos, double ypos);
};

#endif