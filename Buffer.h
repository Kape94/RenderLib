#ifndef _RENDERLIB_BUFFER_H
#define _RENDERLIB_BUFFER_H

#include "_internal/RenderLibNamespaceDefs.h"

#include <initializer_list>

BEGIN_RENDERLIB_NAMESPACE

class Buffer {
  public:

    using ShaderAttribute = struct {
      const unsigned attributeLocation;
      const unsigned nValues;
    };

    using ShaderAttributes = std::initializer_list<ShaderAttribute>;

    void Create(
      const float* vertexData,
      const unsigned nVertexDataItems,
      const ShaderAttributes& shaderAttributes
    );

    void Clear();

    void Render() const;

  private:

    void LinkShaderAttributes(
      const ShaderAttributes& shaderAttributes,
      const unsigned nValuesPerVertex
    ) const;

    unsigned ComputeNumberOfValuesPerVertex(
      const ShaderAttributes& attrs
    ) const;

    unsigned VAO = 0;
    unsigned VBO = 0;
    unsigned IBO = 0;

    unsigned nVertices = 0;
};

END_RENDERLIB_NAMESPACE

#endif
