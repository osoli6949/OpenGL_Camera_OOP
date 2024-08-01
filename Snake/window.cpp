#include "window.h"

using std::runtime_error, std::string;

Window::Window(int width, int height, const char* title)
    : width(width), height(height) {
  if (!glfwInit()) throw std::runtime_error("GLFW failed to initialize.");
  // assume that GLFW is already initialized

  if (width < 0 || height < 0) {
    throw std::invalid_argument("Width or Height cannot be negative");
  }

  this->window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (this->window == NULL) {
    throw runtime_error(string("Failed to create Window: ") + title);
  }

  glfwMakeContextCurrent(this->window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw runtime_error(string("Failed to initialize GLAD in Window: ") +
                        title);
  }

  glfwGetCursorPos(this->window, &this->lastX, &this->lastY);
  this->xoffset = this->yoffset = 0.0f;

  glfwSetWindowUserPointer(this->window, this);
  auto framebufferSizeCallBack = [](GLFWwindow* window, int width, int height) {
    static_cast<Window*>(glfwGetWindowUserPointer(window))
        ->framebuffer_size_callback();
  };
  auto cursorCallBack = [](GLFWwindow* window, double xpos, double ypos) {
    static_cast<Window*>(glfwGetWindowUserPointer(window))
        ->mouse_callback(xpos, ypos);
  };
  glfwSetFramebufferSizeCallback(this->window, framebufferSizeCallBack);
  glfwSetCursorPosCallback(this->window, cursorCallBack);
  glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window() {
  if (this->window != NULL) {
    glfwDestroyWindow(this->window);
  }
}

glm::vec2 Window::getOffset() {
  glm::vec2 ans = glm::vec2(this->xoffset, this->yoffset);
  this->xoffset = 0;
  this->yoffset = 0;
  return ans;
}

void Window::processInput() {
  if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(this->window, true);
}

int Window::shouldClose() { return glfwWindowShouldClose(this->window); }

void Window::swapBuffers() {
  glfwPollEvents();
  glfwSwapBuffers(this->window);
}

void Window::backgroundColor(glm::vec4 color) {
  glClearColor(color[0], color[1], color[2], color[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Framebuffer Callback
void Window::framebuffer_size_callback() const {
  glViewport(0, 0, this->width, this->height);
}

// Mouse Offset Callback
void Window::mouse_callback(double xpos, double ypos) {
  this->xoffset = xpos - this->lastX;
  this->yoffset = this->lastY - ypos;
  this->lastX = xpos;
  this->lastY = ypos;

  // std::cout << xoffset << ", " << yoffset << std::endl;
}