#ifndef CAMERA_H
#define CAMERA_H

#include "window.h"

class Camera : public Window {
 protected:
  // cursor values
  double lastX, lastY;     // cursor position
  float xoffset, yoffset;  // cursor movement

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
  Camera(int width, int height, const char* title, glm::vec3 position,
         glm::vec3 up, float yaw, float pitch);
  glm::mat4 getView() const {
    return glm::lookAt(this->position, this->position + this->front,
                       this->worldUp);
  }

  void processInput(float deltaTime) override;
  void updateCameraVectors();
  void lookAround(bool constrainPitch);

  // callbacks
  void mouse_callback(double xpos, double ypos);
};

#endif  // !CAMERA_H
