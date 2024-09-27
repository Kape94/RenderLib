#include "Buffer.h"

#include "_internal/OpenGLDefs.h"

USING_RENDERLIB_NAMESPACE

//---------------------------------------------------------------------------------------

Buffer::Buffer(
  Buffer&& other
) noexcept :
  VAO(other.VAO),
  VBO(other.VBO),
  EBO(other.EBO),
  instancedVBO(other.instancedVBO),
  nElements(other.nElements),
  isInstanced(other.isInstanced),
  nInstances(other.nInstances)
{
  other.VAO = 0;
  other.VBO = 0;
  other.EBO = 0;
  other.instancedVBO = 0;
  other.nElements = 0;
  other.isInstanced = false;
  other.nInstances = 0;
}

//---------------------------------------------------------------------------------------

Buffer& Buffer::operator=(
  Buffer&& other
) noexcept
{
  if (&other != this) {
    VAO = other.VAO;
    VBO = other.VBO;
    EBO = other.EBO;
    instancedVBO = other.instancedVBO;
    nElements = other.nElements;
    isInstanced = other.isInstanced;
    nInstances = other.nInstances;

    other.VAO = 0;
    other.VBO = 0;
    other.EBO = 0;
    other.instancedVBO = 0;
    other.nElements = 0;
    other.isInstanced = false;
    other.nInstances = 0;
  }

  return *this;
}

//---------------------------------------------------------------------------------------

Buffer::Buffer(
  const std::vector<float>& vertexData,
  const std::vector<unsigned>& indexData,
  const ShaderAttributes& shaderAttributes
)
{
  Create(vertexData, indexData, shaderAttributes);
}

//---------------------------------------------------------------------------------------

Buffer::Buffer(
  const float* vertexData,
  const unsigned nVertexDataItems,
  const unsigned* indexData,
  const unsigned nIndexDataItems,
  const ShaderAttributes& shaderAttributes
)
{
  Create(vertexData, nVertexDataItems, indexData, nIndexDataItems, shaderAttributes);
}

//---------------------------------------------------------------------------------------

Buffer::~Buffer()
{
  Clear();
}

//---------------------------------------------------------------------------------------

void Buffer::Create(
  const std::vector<float>& vertexData,
  const std::vector<unsigned>& indexData,
  const ShaderAttributes& shaderAttributes
)
{
  const unsigned vertexDataSize = static_cast<unsigned>(vertexData.size());
  const unsigned indexDataSize = static_cast<unsigned>(indexData.size());
  Create(vertexData.data(), vertexDataSize, indexData.data(), indexDataSize, shaderAttributes);
}

//---------------------------------------------------------------------------------------

void Buffer::Create(
  const float* vertexData,
  const unsigned nVertexDataItems,
  const unsigned* indexData,
  const unsigned nIndexDataItems,
  const ShaderAttributes& shaderAttributes
)
{
  Clear();

  LoadDataInGPU(vertexData, nVertexDataItems, indexData, nIndexDataItems);
  LinkShaderAttributes(shaderAttributes);

  this->nElements = nIndexDataItems;
}

//---------------------------------------------------------------------------------------

void Buffer::CreateInstanced(
  const float* vertexData,
  const unsigned nVertexDataItems,
  const unsigned* indexData,
  const unsigned nIndexDataItems,
  const ShaderAttributes& shaderAttributes,
  const void* instancedData,
  const unsigned instanceDataSize,
  const unsigned nInstances,
  const ShaderAttributes& instanceShaderAttributes
)
{
  Create(vertexData, nVertexDataItems, indexData, nIndexDataItems, shaderAttributes);

  LoadInstancedDataInGPU(instancedData, instanceDataSize, nInstances);
  LinkInstancedShaderAttributes(instanceShaderAttributes);

  this->isInstanced = true;
  this->nInstances = nInstances;
}

//---------------------------------------------------------------------------------------

void Buffer::LoadDataInGPU(
  const float* vertexData,
  const unsigned nVertexDataItems,
  const unsigned* indexData,
  const unsigned nIndexDataItems
)
{
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  LoadVertexDataInGPU(vertexData, nVertexDataItems);
  LoadIndexDataInGPU(indexData, nIndexDataItems);
}

//---------------------------------------------------------------------------------------

void Buffer::LoadVertexDataInGPU(
  const float* vertexData,
  const unsigned nVertexDataItems
)
{
  const unsigned vertexDataSize = nVertexDataItems * sizeof(float);
  this->VBO = CreateBufferAndLoadData(GL_ARRAY_BUFFER, vertexData, vertexDataSize);
}

//---------------------------------------------------------------------------------------

void Buffer::LoadIndexDataInGPU(
  const unsigned* indexData,
  const unsigned nIndexDataItems
)
{
  const unsigned indexDataSize = nIndexDataItems * sizeof(unsigned);
  this->EBO = CreateBufferAndLoadData(GL_ELEMENT_ARRAY_BUFFER, indexData, indexDataSize);
}

//---------------------------------------------------------------------------------------

void Buffer::LoadInstancedDataInGPU(
  const void* instancedData,
  const unsigned instanceDataSize,
  const unsigned nInstances
)
{
  this->instancedVBO = CreateBufferAndLoadData(
    GL_ARRAY_BUFFER,
    instancedData,
    instanceDataSize * nInstances
  );
}

//---------------------------------------------------------------------------------------

unsigned Buffer::CreateBufferAndLoadData(
  const unsigned bufferType,
  const void* data,
  const unsigned dataSize
)
{
  unsigned newVBO;
  glGenBuffers(1, &newVBO);
  glBindBuffer(bufferType, newVBO);

  glBufferData(bufferType, dataSize, data, GL_STATIC_DRAW);

  return newVBO;
}

//---------------------------------------------------------------------------------------

void Buffer::LinkShaderAttributes(
  const ShaderAttributes& shaderAttributes
) const
{
  const unsigned totalVertexSize = ComputeTotalSizeOfAttributes(shaderAttributes);

  unsigned offset = 0;
  for (const ShaderAttribute& attribute : shaderAttributes) {
    LinkShaderAttribute(attribute, offset, totalVertexSize);

    offset += attribute.DataSizeInBytes();
  }
}

//---------------------------------------------------------------------------------------

void Buffer::LinkShaderAttribute(
  const ShaderAttribute& attr,
  const unsigned offset,
  const unsigned totalAttributeSize
) const
{
  const unsigned location = attr.Location();

  glVertexAttribPointer(
    location,
    attr.NEntries(),
    attr.DataType(),
    GL_FALSE,
    totalAttributeSize,
    (void*)offset
  );
  glEnableVertexAttribArray(location);
}

//---------------------------------------------------------------------------------------

unsigned Buffer::ComputeTotalSizeOfAttributes(
  const ShaderAttributes& attrs
) const
{
  unsigned totalSize = 0;
  for (const ShaderAttribute& attr : attrs) {
    totalSize += attr.DataSizeInBytes();
  }
  return totalSize;
}

//---------------------------------------------------------------------------------------

void Buffer::LinkInstancedShaderAttributes(
  const ShaderAttributes& attrs
) const
{
  LinkShaderAttributes(attrs);
  for (const ShaderAttribute& attr : attrs) {
    glVertexAttribDivisor(attr.Location(), 1);
  }
}

//---------------------------------------------------------------------------------------

void Buffer::Clear()
{
  if (VAO != 0) {
    glDeleteVertexArrays(1, &VAO);
    VAO = 0;
  }
  if (VBO != 0) {
    glDeleteBuffers(1, &VBO);
    VBO = 0;
  }
  if (EBO != 0) {
    glDeleteBuffers(1, &EBO);
    EBO = 0;
  }
  if (instancedVBO != 0) {
    glDeleteBuffers(1, &instancedVBO);
    instancedVBO = 0;
  }
}

//---------------------------------------------------------------------------------------

void Buffer::Render() const
{
  glBindVertexArray(VAO);
  if (this->isInstanced) {
    glDrawElementsInstanced(GL_TRIANGLES, nElements, GL_UNSIGNED_INT, 0, nInstances);
  }
  else {
    glDrawElements(GL_TRIANGLES, nElements, GL_UNSIGNED_INT, 0);
  }
}

//---------------------------------------------------------------------------------------
