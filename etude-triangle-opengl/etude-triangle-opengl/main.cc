// This code is a replica of shaders_interpolation.cpp, which is in
// Joey de Vries' LearnOpenGL, which is licensed under CC BY-NC 4.0.
// Check the website below:
// https://github.com/JoeyDeVries/LearnOpenGL/blob/master/src/1.getting_started/3.2.shaders_interpolation/shaders_interpolation.cpp
// https://learnopengl.com/About
// https://creativecommons.org/licenses/by-nc/4.0/legalcode

#include <cstdint>
#include <ctime>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdint.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// the width and height of the image
constexpr uint16_t kWidth  = 1024;
constexpr uint16_t kHeight = 1024;

// vertex shader source
const char* vertexShaderSource =
  "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "layout (location = 1) in vec3 aColor;\n"
  "out vec3 ourColor;\n"
  "void main() {\n"
  "  gl_Position = vec4(aPos, 1.0);\n"
  "  ourColor = aColor;\n"
  "}";

// fragment shader source
const char* fragmentShaderSource =
  "#version 330 core\n"
  "out vec4 FragColor;\n"
  "in vec3 ourColor;\n"
  "void main() {\n"
  "  FragColor = vec4(ourColor, 1.0f);\n"
  "}";

int main() {
  using std::cerr;
  using std::cout;
  using std::endl;

  // initializion of GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // initializtion of the window
  GLFWwindow* window = glfwCreateWindow(kWidth, kHeight,
      "etude-triangle-opengl", nullptr, nullptr);
  if (nullptr == window) {
    cerr << "Failed to create GLFW window" << endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // initialization of GLAD
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    cerr << "Failed to initialize GLAD" << endl;
    glfwTerminate();
    return -1;
  }

  // build, compile, and link shader programs
  uint32_t vertexShader   = glCreateShader(GL_VERTEX_SHADER);
  uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  uint32_t shaderProgram  = glCreateProgram();
  int32_t success;
  char infoLog[512];
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, sizeof infoLog, nullptr, infoLog);
    cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << endl
         << infoLog << endl;
  }
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, sizeof infoLog, nullptr, infoLog);
    cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << endl
         << infoLog << endl;
  }
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, sizeof infoLog, nullptr, infoLog);
    cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << endl
         << infoLog << endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // set up vertex data and attributes
  float vertices[] = {
    // positions        // colors
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top
  };

  uint32_t VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
      reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
      reinterpret_cast<void*>(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glUseProgram(shaderProgram);

  // initialization of the timer
  struct timespec time_start = {0, 0}, time_end = {0, 0};

  // render loops
  while (!glfwWindowShouldClose(window)) {
    // handle keyboard inputs
    processInput(window);

    // start the timer
    clock_gettime(CLOCK_REALTIME, &time_start);

    // set the background black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // render the triangle
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // stop the timer, calculate the duration and print that
    clock_gettime(CLOCK_REALTIME, &time_end);
    double costTime = (time_end.tv_sec - time_start.tv_sec) * 1e9 +
        time_end.tv_nsec - time_start.tv_nsec;
    // cout << "duration: " << costTime << "ms" << endl;
    printf("duration: %.7fms\n", costTime / 1e6);
    glfwSetWindowShouldClose(window, true); // comment this

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);
  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}