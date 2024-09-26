#ifndef _RENDERLIB_SHADER_ATTRIBUTE_H
#define _RENDERLIB_SHADER_ATTRIBUTE_H

#include <vector>

#include "_internal/RenderLibNamespaceDefs.h"

BEGIN_RENDERLIB_NAMESPACE

class ShaderAttribute {
  public:

    static ShaderAttribute Float(
      const unsigned location,
      const unsigned nEntries
    );

    static ShaderAttribute Double(
      const unsigned location,
      const unsigned nEntries
    );

    static ShaderAttribute Int(
      const unsigned location,
      const unsigned nEntries
    );

    static ShaderAttribute UnsignedInt(
      const unsigned location,
      const unsigned nEntries
    );

    static ShaderAttribute Short(
      const unsigned location,
      const unsigned nEntries
    );

    static ShaderAttribute UnsignedShort(
      const unsigned location,
      const unsigned nEntries
    );

    static ShaderAttribute Byte(
      const unsigned location,
      const unsigned nEntries
    );

    static ShaderAttribute UnsignedByte(
      const unsigned location,
      const unsigned nEntries
    );

    unsigned Location() const;
    unsigned NEntries() const;
    unsigned DataType() const;
    unsigned DataSizeInBytes() const;

  private:

    ShaderAttribute() = default;

    ShaderAttribute(
      const unsigned _location,
      const unsigned _nEntries,
      const unsigned _dataType
    );

    const unsigned location;
    const unsigned nEntries;
    const unsigned dataType;
    const unsigned dataSizeInBytes;
};

using ShaderAttributes = std::vector<ShaderAttribute>;

END_RENDERLIB_NAMESPACE

#endif
