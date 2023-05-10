#include "RenderLib.h"

#include "OpenGLDefs.h"

//---------------------------------------------------------------------------------------

void RenderLib::Initialize() {
  glewExperimental = true;
  glewInit();
}

//---------------------------------------------------------------------------------------
