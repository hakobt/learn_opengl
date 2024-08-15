#include <fstream>
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <sstream>
#include <string>


void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

const GLchar *readShaderFile(std::string const &filename);

int main() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // const auto vertexShaderSource = readShaderFile("default.vert");
  const std::string fullPath = SHADERS_DIR "/default.vert";
  std::cout << fullPath << std::endl;

  std::ifstream file(fullPath);

  std::stringstream ss;
  ss << file.rdbuf();
  std::string str = ss.str();
  const GLchar* g = str.c_str();
  auto vert = &g;
  std::cout << vert << std::endl;
  glShaderSource(vertexShader, 1, vert, nullptr);
  glCompileShader(vertexShader);

  const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  const std::string fllPath = SHADERS_DIR "/default.frag";

  std::ifstream f(fllPath);

  std::stringstream s;
  s << f.rdbuf();
  std::string st = s.str();
  const GLchar* b = st.c_str();
  auto frag = &b;
  std::cout << vert << std::endl;
  glShaderSource(fragmentShader, 1, frag, nullptr);
  glCompileShader(fragmentShader);

  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }


  const int program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);


  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  const float vertices[] = {
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f
  };

  const int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  unsigned int VBO, VAO, EBO;
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *) 0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(program);
  glfwTerminate();
  return 0;
}

const GLchar *readShaderFile(std::string const &filename) {
  const std::string fullPath = SHADERS_DIR "/" + filename;
  std::cout << fullPath << std::endl;

  std::ifstream file(fullPath);

  std::stringstream ss;
  ss << file.rdbuf();
  std::string str = ss.str();
  const GLchar* g = str.c_str();

  return g;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
