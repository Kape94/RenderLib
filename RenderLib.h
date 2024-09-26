#ifndef _RENDERLIB_H
#define _RENDERLIB_H

#include "_internal/RenderLibNamespaceDefs.h"

BEGIN_RENDERLIB_NAMESPACE

void Initialize();

void SetViewport(
  const unsigned x,
  const unsigned y,
  const unsigned width,
  const unsigned height
);

void Clear(
  const float r = 0.0f,
  const float g = 0.0f,
  const float b = 0.0f,
  const float a = 0.0f
);

END_RENDERLIB_NAMESPACE


#endif
