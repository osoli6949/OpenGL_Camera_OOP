#include "camera.h"
using namespace glm;

Camera::Camera(GLFWwindow* window, vec3 position, vec3 up, float yaw,
               float pitch) {
  this->window = window;
  this->position = position;
  this->worldUp = up;
  this->yaw = yaw;
  this->pitch = pitch;

  updateCameraVectors();
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

void Camera::walkAround(float deltaTime) {
  float walkSpeed = this->speed * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    this->position += walkSpeed * this->front;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    this->position -= walkSpeed * this->front;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    this->position -= walkSpeed * normalize(cross(this->front, this->up));
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    this->position += walkSpeed * normalize(cross(this->front, this->up));
  }
}

void Camera::lookAround(vec2 offset, bool constrainPitch) {
  this->yaw += offset[0] * this->sensitivity;
  this->pitch += offset[1] * this->sensitivity;

  if (constrainPitch) {
    if (this->pitch > 89.0f) this->pitch = 89.0f;
    if (this->pitch < -89.0f) this->pitch = -89.0f;
  }
  updateCameraVectors();
}
