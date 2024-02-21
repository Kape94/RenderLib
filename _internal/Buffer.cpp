#include "Buffer.h"

#include "_internal/OpenGLDefs.h"

USING_RENDERLIB_NAMESPACE

//---------------------------------------------------------------------------------------

constexpr unsigned FLOAT_SIZE = sizeof(float);

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
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, nVertexDataItems * sizeof(float), vertexData, GL_STATIC_DRAW);
}

//---------------------------------------------------------------------------------------

void Buffer::LoadIndexDataInGPU(
  const unsigned* indexData,
  const unsigned nIndexDataItems
)
{
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndexDataItems * sizeof(unsigned), indexData, GL_STATIC_DRAW);
}

//---------------------------------------------------------------------------------------

void Buffer::LinkShaderAttributes(
  const ShaderAttributes& shaderAttributes
) const
{
  const unsigned nValuesPerVertex = ComputeNumberOfValuesPerVertex(shaderAttributes);
  const unsigned totalVertexSize = nValuesPerVertex * FLOAT_SIZE;

  unsigned offset = 0;
  for (const ShaderAttribute& attribute : shaderAttributes) {
    const unsigned attributeLocation = attribute.attributeLocation;
    const unsigned nValues = attribute.nValues;
    glVertexAttribPointer(attributeLocation, nValues, GL_FLOAT, GL_FALSE, totalVertexSize, (void*)offset);
    glEnableVertexAttribArray(attributeLocation);

    offset += nValues * FLOAT_SIZE;
  }
}

//---------------------------------------------------------------------------------------

unsigned Buffer::ComputeNumberOfValuesPerVertex(
  const ShaderAttributes& attrs
) const
{
  unsigned nAttributeValues = 0;
  for (const ShaderAttribute& attr : attrs) {
    nAttributeValues += attr.nValues;
  }
  return nAttributeValues;
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
}

//---------------------------------------------------------------------------------------

void Buffer::Render() const
{
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, nElements, GL_UNSIGNED_INT, 0);
}

//---------------------------------------------------------------------------------------
