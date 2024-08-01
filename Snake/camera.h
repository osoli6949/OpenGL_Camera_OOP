#ifndef CAMERA_H
#define CAMERA_H

#include "window.h"

class Camera {
 protected:
  // window pointer
  GLFWwindow* window;

  // camera angles
  float yaw = -90.0f;
  float pitch = 0.0f;

  // camera options
  float speed = 2.5f;
  float sensitivity = 0.1f;
  float fov = 45.0f;

  // camera coords
  glm::vec3 position, front, up, right;
  glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

 public:
  Camera(GLFWwindow* window, glm::vec3 position, glm::vec3 up, float yaw,
         float pitch);
  glm::mat4 getView() const {
    return glm::lookAt(this->position, this->position + this->front,
                       this->worldUp);
  }

  void updateCameraVectors();
  void walkAround(float deltaTime);
  void lookAround(glm::vec2 offset, bool constrainPitch);
};

#endif  // !CAMERA_H
