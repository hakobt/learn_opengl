//
// Created by Hakob on 16.08.24.
//

#ifndef SHADER_HPP
#define SHADER_HPP
#include <string>

#endif //SHADER_HPP

using namespace std;

class Shader
{
public:
  unsigned int ProgramID;
  Shader(string vertexPath, string fragmentPath);
};
