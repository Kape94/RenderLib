#ifndef _RENDERLIB_BUFFER_H
#define _RENDERLIB_BUFFER_H

#include "_internal/RenderLibNamespaceDefs.h"

#include <initializer_list>
#include <vector>

BEGIN_RENDERLIB_NAMESPACE

class Buffer {
  public:

    using ShaderAttribute = struct {
      const unsigned attributeLocation;
      const unsigned nValues;
    };

    using ShaderAttributes = std::initializer_list<ShaderAttribute>;

    void Create(
      const std::vector<float>& vertexData,
      const std::vector<unsigned>& indexData,
      const ShaderAttributes& shaderAttributes
    );

    void Create(
      const float* vertexData,
      const unsigned nVertexDataItems,
      const unsigned* indexData,
      const unsigned nIndexDataItems,
      const ShaderAttributes& shaderAttributes
    );

    void Clear();

    void Render() const;

  private:

    void LoadDataInGPU(
      const float* vertexData,
      const unsigned nVertexDataItems,
      const unsigned* indexData,
      const unsigned nIndexDataItems
    );

    void LoadVertexDataInGPU(
      const float* vertexData,
      const unsigned nVertexDataItems
    );

    void LoadIndexDataInGPU(
      const unsigned* indexData,
      const unsigned nIndexDataItems
    );

    void LinkShaderAttributes(
      const ShaderAttributes& shaderAttributes
    ) const;

    unsigned ComputeNumberOfValuesPerVertex(
      const ShaderAttributes& attrs
    ) const;

    unsigned VAO = 0;
    unsigned VBO = 0;
    unsigned EBO = 0;

    unsigned nElements = 0;
};

END_RENDERLIB_NAMESPACE

#endif
