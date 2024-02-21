#include "Shader.h"

#include "_internal/OpenGLDefs.h"

USING_RENDERLIB_NAMESPACE

//---------------------------------------------------------------------------------------

Shader::Shader(
  const char* vertexShaderCode,
  const char* fragmentShaderCode
)
{
  Create(vertexShaderCode, fragmentShaderCode);
}

//---------------------------------------------------------------------------------------

Shader::~Shader()
{
  Clear();
}

//---------------------------------------------------------------------------------------

void Shader::Create(
  const char* vertexShaderCode,
  const char* fragmentShaderCode
)
{
  Clear();

  const unsigned vShaderID = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vShaderID, 1, &vertexShaderCode, nullptr);
  glCompileShader(vShaderID);
 
  const unsigned fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fShaderID, 1, &fragmentShaderCode, nullptr);
  glCompileShader(fShaderID);

  id = glCreateProgram();
  glAttachShader(id, vShaderID);
  glAttachShader(id, fShaderID);
  glLinkProgram(id);

  glDeleteShader(vShaderID);
  glDeleteShader(fShaderID);
}

//---------------------------------------------------------------------------------------

void Shader::Use()
{
  glUseProgram(id);
}

//---------------------------------------------------------------------------------------

void Shader::SetUniform(
  const std::string& name,
  const TextureUnit& unit
)
{
  const int location = glGetUniformLocation(id, name.c_str());
  if (location != -1) {
    glProgramUniform1i(id, location, static_cast<unsigned>(unit));
  }
}

//---------------------------------------------------------------------------------------

void Shader::Clear()
{
  if (id != 0) {
    glDeleteProgram(id);
    id = 0;
  }
}

//---------------------------------------------------------------------------------------
