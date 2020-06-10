#ifndef CELL_SHADERUNIFORM1_TYPES_H
#define CELL_SHADERUNIFORM1_TYPES_H

#include <math/linear_algebra/vmath.h>
#include "glad/glad.h"
#include <string>
#include <memory>
#include <array>
#include "shading/shading_types.h"
#include "shader.h"
namespace Cell
{
	class Texture;
	class TextureCube;

	class UniformBase
	{
	public:
		UniformBase(const std::string& name) :uniformName(name) {}
	public:
		std::string uniformName;
		SHADER_TYPE Type;
		bool dirty;
		virtual void UpLoad(Shader* Shader) = 0;
	};
	template <typename T, size_t COUNT = 1>
	class UniformValue :public UniformBase
	{
	public:
		UniformValue() = default;
		using type = typename std::enable_if <
			std::is_same<GLboolean, T>::value ||
			std::is_same<GLint, T>::value ||
			std::is_same<GLfloat, T>::value ||
			std::is_same<math::vec2f, T>::value ||
			std::is_same<math::vec3f, T>::value ||
			std::is_same<math::vec4f, T>::value ||
			std::is_same<math::mat3f, T>::value ||
			std::is_same<math::mat4f, T>::value, T>::type;

		UniformValue(std::string const& name, type const& v0) :UniformBase(name)
		{
			value[0] = v0;
			if (std::is_same<type, GLboolean>::value)
			{
				Type = SHADER_TYPE_BOOL;
			}
			else if (std::is_same<type, GLint>::value)
			{
				Type = SHADER_TYPE_INT;
			}
			else if (std::is_same<type, GLfloat>::value)
			{
				Type = SHADER_TYPE_FLOAT;
			}
			else if (std::is_same<type, math::vec2f>::value)
			{
				Type = SHADER_TYPE_VEC2;
			}
			else if (std::is_same<type, math::vec3f>::value)
			{
				Type = SHADER_TYPE_VEC3;
			}
			else if (std::is_same<type, math::mat3f>::value)
			{
				Type = SHADER_TYPE_MAT3;
			}
			else if (std::is_same<type, math::mat4f>::value)
			{
				Type = SHADER_TYPE_MAT4;
			}
		}

		std::array<type,COUNT> value;
		//std::vector<type> value;
		
		void Set(type const& v)
		{
			value[0] = v;
			dirty = true;
		}
		
		void UpLoad(Shader* shader)
		{
			std::cout << "you should not be here" << std::endl;
		}
	};
	using UniformValueBasePtr = std::shared_ptr<UniformBase>;

	template<>
	inline void UniformValue<GLint, 1>::UpLoad(Shader* shader)
	{
		if (!dirty)return;
		if (!shader)return;
		shader->SetInt(uniformName, value[0]);
	}
	template<>
	inline void UniformValue<GLfloat, 1>::UpLoad(Shader* shader)
	{
		if (!dirty)return;
		if (!shader)return;
		shader->SetFloat(uniformName, value[0]);
	}
	template<>
	inline void UniformValue<GLboolean, 1>::UpLoad(Shader* shader)
	{
		if (!dirty)return;
		if (!shader)return;
		shader->SetBool(uniformName, value[0]);
	}
	template<>
	inline void UniformValue<math::vec2f, 1>::UpLoad(Shader* shader)
	{
		if (!dirty)return;
		if (!shader)return;
		shader->SetVector(uniformName, value[0]);
	}
	template<>
	inline void UniformValue<math::vec3f, 1>::UpLoad(Shader* shader)
	{
		if (!dirty)return;
		if (!shader)return;
		shader->SetVector(uniformName, value[0]);
	}
	template<>
	inline void UniformValue<math::vec4f, 1>::UpLoad(Shader* shader)
	{
		if (!dirty)return;
		if (!shader)return;
		shader->SetVector(uniformName, value[0]);
	}
	template<>
	inline void UniformValue<math::mat3f, 1>::UpLoad(Shader* shader)
	{
		if (!dirty)return;
		if (!shader)return;
		shader->SetMatrix(uniformName, value[0]);
	}
	template<>
	inline void UniformValue<math::mat4f, 1>::UpLoad(Shader* shader)
	{
		if (!dirty)return;
		if (!shader)return;
		shader->SetMatrix(uniformName, value[0]);
	}
	struct UniformValueSampler
	{
		SHADER_TYPE  Type;
		unsigned int Unit;
		Texture     *Texture;
		TextureCube *TextureCube;
		bool isDirty;
		UniformValueSampler() {}
	};


}

#endif