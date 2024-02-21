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

END_RENDERLIB_NAMESPACE


#endif
