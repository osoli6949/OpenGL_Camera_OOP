#include <Windows.h>

#include "camera.h"
#include "objects.h"
#include "shader.h"
#include "texture.h"

using std::vector, std::string;
using namespace glm;
vector<float> VERTICES = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // 1
    0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,  // 2
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,  // 3
    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f,  // 4

    -0.5f, -0.5f, 0.5f,  1.0f, 0.0f,  // 5
    0.5f,  -0.5f, 0.5f,  0.0f, 0.0f,  // 6
    0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // 7
    -0.5f, 0.5f,  0.5f,  1.0f, 1.0f,  // 8

    -0.5f, -0.5f, 0.5f,  0.0f, 1.0f,  // 9
    0.5f,  -0.5f, 0.5f,  1.0f, 1.0f,  // 10
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  // 11
    -0.5f, 0.5f,  0.5f,  0.0f, 0.0f,  // 12
};
vector<unsigned int> INDICES = {
    0, 1, 2,  2,  3,  0,  // 1 2 3 4
    4, 5, 6,  6,  7,  4,  // 5 6 7 8
    1, 2, 6,  6,  5,  1,  // 2 3 7 6
    0, 3, 7,  7,  4,  0,  // 1 4 8 5
    2, 3, 11, 11, 10, 2,  // 3 4 12 11
    1, 0, 8,  8,  9,  1   // 2 1 9 10
};

// shader paths
string VERTEX_SHADER_PATH = "./shaders/vertex_shader.glsl";
string FRAGMENT_SHADER_PATH = "./shaders/fragment_shader.glsl";

// texture paths
string TEXTURE_PATH_CONTAINER = "./textures/container.jpg";
string TEXTURE_PATH_DVD = "./textures/DVD.png";
string TEXTURE_PATH_FACE = "./textures/awesomeface.png";

// color value
vec4 BACKGROUND_COLOR(0.2f, 0.3f, 0.3f, 1.0f);

// window size
int WIDTH = 800;
int HEIGHT = 600;

// frame measure
float deltaTime = 0.0f;  // Time between current frame and last frame
float lastFrame = 0.0f;  // Time of last frame

// cube positions
vec3 cubePositions[] = {vec3(0.0f, 0.0f, 0.0f),    vec3(2.0f, 5.0f, -15.0f),
                        vec3(-1.5f, -2.2f, -2.5f), vec3(-3.8f, -2.0f, -12.3f),
                        vec3(2.4f, -0.4f, -3.5f),  vec3(-1.7f, 3.0f, -7.5f),
                        vec3(1.3f, -2.0f, -2.5f),  vec3(1.5f, 2.0f, -2.5f),
                        vec3(1.5f, 0.2f, -1.5f),   vec3(-1.3f, 1.0f, -1.5f)};

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // window (with camera)
  Camera W(WIDTH, HEIGHT, "Snake", vec3(0.0f, 0.0f, 0.0f),
           vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f);

  // objects
  VAO VAO;
  VBO VBO(VERTICES);
  EBO EBO(INDICES);

  VBO.vertexAttrib(0, 3, 5, 0);  // vertex position
  VBO.vertexAttrib(1, 2, 5, 3);  // texture coords

  // textures
  Texture container(TEXTURE_PATH_CONTAINER, GL_RGB, GL_TEXTURE0);
  Texture awesomeface(TEXTURE_PATH_FACE, GL_RGBA, GL_TEXTURE1);

  // shaders
  Shader vertex(GL_VERTEX_SHADER, VERTEX_SHADER_PATH);
  Shader fragment(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_PATH);
  ShaderProgram shaderProgram(vertex.getAddress(), fragment.getAddress());

  shaderProgram.use();
  shaderProgram.setUniform1i("texture1", 0);
  shaderProgram.setUniform1i("texture2", 1);
  glEnable(GL_DEPTH_TEST);

  // render loop
  while (!W.shouldClose()) {
    // frame measurement
    float currentFrame = glfwGetTime();  // Time of current frame
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // input process & background color
    W.processInput(deltaTime);
    W.backgroundColor(BACKGROUND_COLOR);

    // MVP matrix
    mat4 model;
    mat4 view = W.getView();
    mat4 projection =
        perspective(radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    // shader & uniform binding
    shaderProgram.use();
    shaderProgram.setUniformMatrix4fv("view", view);
    shaderProgram.setUniformMatrix4fv("projection", projection);

    // texture
    container.active();
    awesomeface.active();

    // draw
    VAO.bind();
    for (size_t i = 0; i < 10; i++) {
      model = mat4(1.0f);
      model = translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model = rotate(model, (float)glfwGetTime() * radians(45.0f) + angle,
                     vec3(0.5f, 1.0f, 0.0f));
      shaderProgram.setUniformMatrix4fv("model", model);
      EBO.draw(GL_TRIANGLES, 36, 0);
    }

    glfwPollEvents();
    W.swapBuffers();
  }

  glfwTerminate();
  return 0;
}