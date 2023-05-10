#ifndef _RENDERLIB_SHADER_H
#define _RENDERLIB_SHADER_H

#include "_internal/RenderLibNamespaceDefs.h"

BEGIN_RENDERLIB_NAMESPACE

class Shader {
  public:

    void Create(
      const char* vertexShaderCode,
      const char* fragmentShaderCode
    );

    void Use();

  private:

    unsigned id;
};

END_RENDERLIB_NAMESPACE

#endif
