#ifndef INCLUDE_PASTORSETYPES_H_
#define INCLUDE_PASTORSETYPES_H_ 1

#include <stdint.h>

/// Creates a Unique_PTR
#define CREATE_UNIQUE_PTR(var1) std::unique_ptr<var1>(new var1());
/// Creates a Shared_PTR
#define CREATE_MAKE_SHARED_PTR(var1) std::shared_ptr<var1>(new var1())

enum ShaderType{
  kShaderType_Basic,
  kShaderType_Texture,
  kShaderType_RenderToTexture,
  kShaderType_RenderToTextureRed,
  kShaderType_RenderToTextureGreen,
  kShaderType_Light_Basic,
  kShaderType_Light_Texture,

  /// De mientras Probando tipos de luz

  kShaderType_DirectionalLight_Texture, 
  kShaderType_TestDirectionalLight_Texture,
  kShaderType_PointLight_Texture,
  kShaderType_SpotLight_Texture,
  kShaderType_TestSpotLight_Texture,
  kShaderType_TestSpotDirectionalLight_Texture,
  kShaderType_3SpotDirectionalLight_Texture,


  /// Sombras
  kShaderType_RenderPosition,

};

/// Remember: Signed allows negative values.

/// Signed Char
typedef ::int8_t int8; 
/// Short
typedef ::int16_t int16;
/// Int
typedef ::int32_t int32;
/// Long Long
typedef ::int64_t int64;
	

/// Unsigned Char
typedef ::uint8_t uint8;
/// Unsigned Short
typedef ::uint16_t uint16;
/// Unsigned Int
typedef ::uint32_t uint32;
/// Unsigned Long Long
typedef ::uint64_t uint64;

typedef char char8;

// Float
typedef float float32;

#endif
		