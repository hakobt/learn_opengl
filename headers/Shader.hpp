//
// Created by Hakob on 16.08.24.
//

#ifndef SHADER_HPP
#define SHADER_HPP
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "glad.h"

#endif //SHADER_HPP

class Shader {
public:
  unsigned int ProgramID;

  void use() const {
    glUseProgram(ProgramID);
  }

  void remove() const {
    glDeleteProgram(ProgramID);
  }

  void setFloat(const std::string &name, const float value) const {
    glUniform1f(glGetUniformLocation(ProgramID, name.c_str()), value);
  }

  void setBool(const std::string &name, const bool value) const {
    glUniform1i(glGetUniformLocation(ProgramID, name.c_str()), static_cast<int>(value));
  }

  Shader(const std::string &vertexFile, const std::string &fragmentFile) {
    ProgramID = glCreateProgram();
    attachShader(ProgramID, vertexFile);
    attachShader(ProgramID, fragmentFile);
    glLinkProgram(ProgramID);
    int success;
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &success);
    if (!success) {
      char infoLog[512];
      glGetProgramInfoLog(ProgramID, 512, nullptr, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
  }

private:
  static void attachShader(GLuint program, std::string const &shaderFile) {
    const std::string fullPath = SHADERS_DIR "/" + shaderFile;
    std::ifstream file(fullPath);

    std::stringstream ss;
    ss << file.rdbuf();
    auto shaderStr = ss.str();
    auto source = shaderStr.c_str();
    auto shader = createShader(shaderFile);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      char infoLog[512];
      glGetShaderInfoLog(shader, 512, nullptr, infoLog);
      std::cout << "ERROR::COMPILATION_FAILED FOR\n" << fullPath + "\n" << infoLog << std::endl;
    }

    glAttachShader(program, shader);
    glDeleteShader(shader);
  }

  static int createShader(std::string const &shaderFile) {
    const auto index = shaderFile.rfind('.');
    const auto extension = shaderFile.substr(index + 1);
    if (extension == "vert") {
      return glCreateShader(GL_VERTEX_SHADER);
    }
    if (extension == "frag") {
      return glCreateShader(GL_FRAGMENT_SHADER);
    }
    return 0;
  }
};
