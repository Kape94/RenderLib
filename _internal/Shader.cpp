#include "Shader.h"

#include "_internal/OpenGLDefs.h"

USING_RENDERLIB_NAMESPACE

//---------------------------------------------------------------------------------------

void Shader::Create(
  const char* vertexShaderCode,
  const char* fragmentShaderCode
)
{
  const unsigned vShaderID = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vShaderID, 1, &vertexShaderCode, nullptr);
  glCompileShader(vShaderID);
 
  const unsigned fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fShaderID, 1, &fragmentShaderCode, nullptr);
  glCompileShader(fShaderID);

  this->id = glCreateProgram();
  glAttachShader(this->id, vShaderID);
  glAttachShader(this->id, fShaderID);
  glLinkProgram(this->id);

  glDeleteShader(vShaderID);
  glDeleteShader(fShaderID);
}

//---------------------------------------------------------------------------------------

void Shader::Use()
{
  glUseProgram(this->id);
}

//---------------------------------------------------------------------------------------

void Shader::SetUniform(
  const std::string& name,
  const TextureUnit& unit
)
{
  const int location = glGetUniformLocation(this->id, name.c_str());
  if (location != -1) {
    glProgramUniform1i(this->id, location, static_cast<unsigned>(unit));
  }
}

//---------------------------------------------------------------------------------------

void Shader::Clear()
{
  if (this->id != 0) {
    glDeleteProgram(this->id);
    this->id = 0;
  }
}

//---------------------------------------------------------------------------------------
