#ifndef CELL_SHADING_SHADING_TYPES_H
#define CELL_SHADING_SHADING_TYPES_H

#include <math/linear_algebra/vmath.h>
#include "glad/glad.h"
#include <string>
#include <memory>
namespace Cell
{
	class Texture;
	class TextureCube;

	enum SHADER_TYPE
	{
		SHADER_TYPE_BOOL,
		SHADER_TYPE_INT,
		SHADER_TYPE_FLOAT,
		SHADER_TYPE_SAMPLER1D,
		SHADER_TYPE_SAMPLER2D,
		SHADER_TYPE_SAMPLER3D,
		SHADER_TYPE_SAMPLERCUBE,
		SHADER_TYPE_VEC2,
		SHADER_TYPE_VEC3,
		SHADER_TYPE_VEC4,
		SHADER_TYPE_MAT2,
		SHADER_TYPE_MAT3,
		SHADER_TYPE_MAT4,
	};

	struct Uniform
	{
		SHADER_TYPE  Type;
		std::string  Name;
		int          Size;
		unsigned int Location;
	};

	struct VertexAttribute
	{
		SHADER_TYPE  Type;
		std::string  Name;
		int          Size;
		unsigned int Location;
	};
}
#endif