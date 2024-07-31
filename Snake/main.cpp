#include "objects.h"
#include "shader.h"
#include "window.h"

using std::vector, std::string;
vector<float> VERTICES = {
    0.5f,  0.5f,  0.0f,  // top right
    0.5f,  -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f, 0.5f,  0.0f   // top left
};
vector<unsigned int> INDICES = {
    // note that we start from 0!
    0, 1, 3,  // first triangle
    1, 2, 3   // second triangle
};
string VERTEX_SHADER_PATH = "./shaders/vertex_shader.glsl";
string FRAGMENT_SHADER_PATH = "./shaders/fragment_shader.glsl";

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  Window W(800, 600, "Snake");

  // objects
  VAO VAO;
  VBO VBO(VERTICES);
  EBO EBO(INDICES);
  VBO.vertexAttrib(0, 3, 3, 0);

  // shaders
  Shader vertex(GL_VERTEX_SHADER, VERTEX_SHADER_PATH);
  Shader fragment(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_PATH);
  ShaderProgram shaderProgram(vertex.getAddress(), fragment.getAddress());

  // render loop
  while (!W.shouldClose()) {
    W.processInput();

    // draw
    shaderProgram.use();
    VAO.bind();
    EBO.draw(GL_TRIANGLES, 6, 0);
    VAO.unbind();

    W.swapBuffers();
  }

  glfwTerminate();
  return 0;
}