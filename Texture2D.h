#ifndef _RENDERLIB_TEXTURE_H
#define _RENDERLIB_TEXTURE_H

#include "_internal/RenderLibNamespaceDefs.h"
#include "TextureUnit.h"

BEGIN_RENDERLIB_NAMESPACE

class Texture2D {
  public:

    void Create(
      const unsigned char* data,
      const unsigned width,
      const unsigned height
    );

    void Use(
      const RenderLib::TextureUnit& textureUnit
    );

    void Clear();

  private:

    unsigned id = 0;
};

END_RENDERLIB_NAMESPACE

#endif
