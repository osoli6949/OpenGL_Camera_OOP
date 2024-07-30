#include "camera.h"
Camera::Camera(int width, int height, const char* title, glm::vec3 position,
               glm::vec3 up, float yaw, float pitch)
    : Window(width, height, title) {
  this->position = position;
  this->worldUp = up;
  this->yaw = yaw;
  this->pitch = pitch;

  auto mouseCallBack = [](GLFWwindow* window, double xpos, double ypos) {
    static_cast<Camera*>(glfwGetWindowUserPointer(window))->mouse_callback();
  };
  glfwSetCursorPosCallback(this->window, mouseCallBack);
}

void Camera::mouse_callback() {}