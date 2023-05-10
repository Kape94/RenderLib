#include "Buffer.h"

#include "_internal/OpenGLDefs.h"

USING_RENDERLIB_NAMESPACE

//---------------------------------------------------------------------------------------

constexpr unsigned FLOAT_SIZE = sizeof(float);

//---------------------------------------------------------------------------------------

void Buffer::Create(
  const float* vertexData,
  const unsigned nVertexDataItems,
  const ShaderAttributes& shaderAttributes
)
{
  glGenVertexArrays(1, &this->VAO);
  glBindVertexArray(this->VAO);

  glGenBuffers(1, &this->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

  glBufferData(GL_ARRAY_BUFFER, nVertexDataItems * sizeof(float), vertexData, GL_STATIC_DRAW);

  const unsigned nValuesPerVertex = ComputeNumberOfValuesPerVertex(shaderAttributes);
  this->nVertices = nVertexDataItems / nValuesPerVertex;

  LinkShaderAttributes(shaderAttributes, nValuesPerVertex);
}

//---------------------------------------------------------------------------------------

void Buffer::LinkShaderAttributes(
  const ShaderAttributes& shaderAttributes,
  const unsigned nValuesPerVertex
) const
{
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
  if (IBO != 0) {
    glDeleteBuffers(1, &IBO);
    IBO = 0;
  }
}

//---------------------------------------------------------------------------------------

void Buffer::Render() const
{
  glDrawArrays(GL_TRIANGLES, 0, this->nVertices);
}

//---------------------------------------------------------------------------------------
