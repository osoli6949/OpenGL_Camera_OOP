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

  glfwSetWindowUserPointer(this->window, this);

  auto framebufferSizeCallBack = [](GLFWwindow* window, int width, int height) {
    static_cast<Window*>(glfwGetWindowUserPointer(window))
        ->framebuffer_size_callback();
  };
  glfwSetFramebufferSizeCallback(this->window, framebufferSizeCallBack);
}

Window::~Window() {
  if (this->window != NULL) {
    glfwDestroyWindow(this->window);
  }
}

void Window::processInput() {
  if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(this->window, true);
}

void Window::renderLoop() {
  // rendering loop
  while (!glfwWindowShouldClose(this->window)) {
    this->processInput();

    // ...

    glfwPollEvents();
    glfwSwapBuffers(this->window);
  }
}

// callbacks
void Window::framebuffer_size_callback() {
  glViewport(0, 0, this->width, this->height);
}