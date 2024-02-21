#ifndef _RENDERLIB_SHADER_H
#define _RENDERLIB_SHADER_H

#include "_internal/RenderLibNamespaceDefs.h"
#include "TextureUnit.h"

#include <string>

BEGIN_RENDERLIB_NAMESPACE

class Shader {
  public:

    Shader() = default;

    Shader(
      const char* vertexShaderCode,
      const char* fragmentShaderCode
    );

    ~Shader();

    void Create(
      const char* vertexShaderCode,
      const char* fragmentShaderCode
    );

    void Use();

    void SetUniform(
      const std::string& name,
      const TextureUnit& unit
    );

    void Clear();

  private:

    unsigned id = 0;
};

END_RENDERLIB_NAMESPACE

#endif
