#ifndef CAMERA_H
#define CAMERA_H

#include "window.h"

class Camera : public Window {
 protected:
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
  Camera(int, int, const char*, glm::vec3, glm::vec3, float, float);

  // callbacks
  void mouse_callback();
};

#endif  // !CAMERA_H
