#include "RenderLib.h"

#include "OpenGLDefs.h"

//---------------------------------------------------------------------------------------

void RenderLib::Initialize() {
  glewExperimental = true;
  glewInit();
}

//---------------------------------------------------------------------------------------

void RenderLib::SetViewport(
  const unsigned x,
  const unsigned y,
  const unsigned width,
  const unsigned height
)
{
  glViewport(x, y, width, height);
}

//---------------------------------------------------------------------------------------
