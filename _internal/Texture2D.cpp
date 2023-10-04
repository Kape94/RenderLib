#include "Texture2D.h"

#include "_internal/OpenGLDefs.h"

//---------------------------------------------------------------------------------------

USING_RENDERLIB_NAMESPACE

//---------------------------------------------------------------------------------------

void Texture2D::Create(
  const unsigned char* data,
  const unsigned width,
  const unsigned height
)
{
  glGenTextures(1, &this->id);

  glBindTexture(GL_TEXTURE_2D, this->id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
}

//---------------------------------------------------------------------------------------

void Texture2D::Use(
  const TextureUnit& textureUnit
)
{  
  const unsigned textureUnitID = static_cast<unsigned>(textureUnit);
  glActiveTexture(GL_TEXTURE0 + textureUnitID);
  glBindTexture(GL_TEXTURE_2D, this->id);
}

//---------------------------------------------------------------------------------------

void Texture2D::Clear()
{
  if (this->id != 0) {
    glDeleteTextures(1, &this->id);
    this->id = 0;
  }
}

//---------------------------------------------------------------------------------------
