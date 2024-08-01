#include "camera.h"
using namespace glm;

Camera::Camera(int width, int height, const char* title, vec3 position, vec3 up,
               float yaw, float pitch)
    : Window(width, height, title) {
  glfwGetCursorPos(this->window, &this->lastX, &this->lastY);
  this->xoffset = this->yoffset = 0.0f;

  auto cursorCallBack = [](GLFWwindow* window, double xpos, double ypos) {
    static_cast<Camera*>(glfwGetWindowUserPointer(window))
        ->mouse_callback(xpos, ypos);
  };

  glfwSetCursorPosCallback(this->window, cursorCallBack);
  glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  updateCameraVectors();
}

void Camera::processInput(float deltaTime) {
  float walkSpeed = 2.5f * deltaTime;
  if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(this->window, true);

  if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
    this->position += walkSpeed * this->front;
  if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
    this->position -= walkSpeed * this->front;
  if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
    this->position += walkSpeed * normalize(cross(this->up, this->front));
  if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
    this->position -= walkSpeed * normalize(cross(this->up, this->front));
}

void Camera::updateCameraVectors() {
  vec3 front;
  front.x = cos(radians(this->yaw)) * cos(radians(this->pitch));
  front.y = sin(radians(this->pitch));
  front.z = sin(radians(this->yaw)) * cos(radians(this->pitch));

  this->front = normalize(front);
  this->right = normalize(cross(this->front, this->worldUp));
  this->up = normalize(cross(this->right, this->front));
}

void Camera::lookAround(bool constrainPitch) {
  this->yaw += this->xoffset * this->sensitivity;
  this->pitch += this->yoffset * this->sensitivity;

  if (constrainPitch) {
    if (this->pitch > 89.0f) this->pitch = 89.0f;
    if (this->pitch < -89.0f) this->pitch = -89.0f;
  }

  updateCameraVectors();
}

// Mouse Offset Callback
void Camera::mouse_callback(double xpos, double ypos) {
  this->xoffset = xpos - this->lastX;
  this->yoffset = this->lastY - ypos;

  lookAround(true);

  this->lastX = xpos;
  this->lastY = ypos;
}