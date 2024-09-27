#ifndef _RENDERLIB_BUFFER_H
#define _RENDERLIB_BUFFER_H

#include <vector>

#include "_internal/RenderLibNamespaceDefs.h"

#include "ShaderAttribute.h"

BEGIN_RENDERLIB_NAMESPACE

class Buffer {
  public:

    Buffer() = default;

    Buffer(
      Buffer&& other
    ) noexcept;

    Buffer& operator=(
      Buffer&& other
    ) noexcept;

    Buffer(
      const std::vector<float>& vertexData,
      const std::vector<unsigned>& indexData,
      const ShaderAttributes& shaderAttributes
    );

    Buffer(
      const float* vertexData,
      const unsigned nVertexDataItems,
      const unsigned* indexData,
      const unsigned nIndexDataItems,
      const ShaderAttributes& shaderAttributes
    );

    ~Buffer();

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

    void CreateInstanced(
      const float* vertexData,
      const unsigned nVertexDataItems,
      const unsigned* indexData,
      const unsigned nIndexDataItems,
      const ShaderAttributes& shaderAttributes,
      const void* instancedData,
      const unsigned instancedDataSize,
      const unsigned nInstances,
      const ShaderAttributes& instanceShaderAttributes
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

    void LoadInstancedDataInGPU(
      const void* instancedData,
      const unsigned instanceDataSize,
      const unsigned nInstances
    );

    unsigned CreateBufferAndLoadData(
      const unsigned bufferType,
      const void* data,
      const unsigned dataSize
    );

    void LinkShaderAttributes(
      const ShaderAttributes& shaderAttributes
    ) const;

    void LinkShaderAttribute(
      const ShaderAttribute& attr,
      const unsigned offset,
      const unsigned totalAttributeSize
    ) const;

    unsigned ComputeTotalSizeOfAttributes(
      const ShaderAttributes& attrs
    ) const;

    void LinkInstancedShaderAttributes(
      const ShaderAttributes& attrs
    ) const;

    unsigned VAO = 0;
    unsigned VBO = 0;
    unsigned EBO = 0;
    unsigned instancedVBO = 0;

    unsigned nElements = 0;

    bool isInstanced = false;
    unsigned nInstances = 0;
};

END_RENDERLIB_NAMESPACE

#endif
