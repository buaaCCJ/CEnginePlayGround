#include "material.h"

#include "../resources/resources.h"

namespace Cell
{
    // --------------------------------------------------------------------------------------------
    Material::Material()
    {

    }
    // --------------------------------------------------------------------------------------------
    Material::Material(Shader* shader)
    {
        m_Shader = shader;
		//parser uniforms  from shader to material
		for (int i = 0; i < m_Shader->Uniforms.size(); ++i)
		{
			auto & iter = m_Shader->Uniforms[i];
			switch (iter.Type)
			{
			case SHADER_TYPE::SHADER_TYPE_BOOL:
			{
				m_Uniforms[iter.Name].reset(new UniformValue<GLboolean, 1>(iter.Name, (GLboolean)false));
				m_Uniforms[iter.Name]->dirty = false;
				break;
			}
			case SHADER_TYPE::SHADER_TYPE_FLOAT:
			{
				m_Uniforms[iter.Name].reset(new UniformValue<GLfloat, 1>(iter.Name, 0));
				m_Uniforms[iter.Name]->dirty = false;

				break;
			}
			case SHADER_TYPE::SHADER_TYPE_INT:
			{
				m_Uniforms[iter.Name].reset(new UniformValue<GLint, 1>(iter.Name, 0));
				m_Uniforms[iter.Name]->dirty = false;

				break;
			}
			case SHADER_TYPE::SHADER_TYPE_MAT3:
			{
				m_Uniforms[iter.Name].reset(new UniformValue<math::mat3f, 1>(iter.Name, math::mat3f::Identity));
				m_Uniforms[iter.Name]->dirty = false;

				break;
			}
			case SHADER_TYPE::SHADER_TYPE_MAT4:
			{
				m_Uniforms[iter.Name].reset(new UniformValue<math::mat4f, 1>(iter.Name, math::mat4f::Identity));
				m_Uniforms[iter.Name]->dirty = false;

				break;
			}
			case SHADER_TYPE::SHADER_TYPE_VEC2:
			{
				math::vec2f id;
				m_Uniforms[iter.Name].reset(new UniformValue<math::vec2f, 1>(iter.Name, id));
				m_Uniforms[iter.Name]->dirty = false;

				break;
			}
			case SHADER_TYPE::SHADER_TYPE_VEC3:
			{
				math::vec3f id;
				m_Uniforms[iter.Name].reset(new UniformValue<math::vec3f, 1>(iter.Name, id));
				m_Uniforms[iter.Name]->dirty = false;

				break;
			}
			case SHADER_TYPE::SHADER_TYPE_VEC4:
			{
				math::vec4f id;
				m_Uniforms[iter.Name].reset(new UniformValue<math::vec4f, 1>(iter.Name, id));
				m_Uniforms[iter.Name]->dirty = false;
				break;
			}
			/*case SHADER_TYPE::SHADER_TYPE_SAMPLER2D:
			{
				m_SamplerUniforms[iter.Name].Unit = 0;
				m_SamplerUniforms[iter.Name].Texture = nullptr;
				m_SamplerUniforms[iter.Name].Type = SHADER_TYPE_SAMPLER2D;
				m_SamplerUniforms[iter.Name].isDirty = false;
				break;
			}
			case SHADER_TYPE::SHADER_TYPE_SAMPLERCUBE:
			{
				m_SamplerUniforms[iter.Name].Unit = 0;
				m_SamplerUniforms[iter.Name].Texture = nullptr;
				m_SamplerUniforms[iter.Name].Type = SHADER_TYPE_SAMPLERCUBE;
				m_SamplerUniforms[iter.Name].isDirty = false;

				break;
			}*/
			default:
				break;
			}
		}
    }
    // --------------------------------------------------------------------------------------------
    Shader* Material::GetShader()
    {
        return m_Shader;
    }
    // --------------------------------------------------------------------------------------------
    void Material::SetShader(Shader* shader)
    {
        m_Shader = shader;
    }
    // --------------------------------------------------------------------------------------------
    Material Material::Copy()
    {
        Material copy(m_Shader);

        copy.Type = Type;

        copy.Color = Color;
        
        copy.DepthTest = DepthTest;
        copy.DepthWrite = DepthWrite;
        copy.DepthCompare = DepthCompare;

        copy.Cull = Cull;
        copy.CullFace = CullFace;
        copy.CullWindingOrder = CullWindingOrder;

        copy.Blend = Blend;
        copy.BlendSrc = BlendSrc;
        copy.BlendDst = BlendDst;
        copy.BlendEquation = BlendEquation;

        copy.m_Uniforms = m_Uniforms;
        copy.m_SamplerUniforms = m_SamplerUniforms;
        
        return copy;
    }
    // --------------------------------------------------------------------------------------------
    void Material::SetBool(std::string name, bool value)
    {
		m_Uniforms[name].reset(new UniformValue<GLboolean,1>(name,(GLboolean)value));
    }
    // --------------------------------------------------------------------------------------------
    void Material::SetInt(std::string name, int value)
    {
      /*  m_Uniforms[name].Type = SHADER_TYPE_INT;
        m_Uniforms[name].Int  = value;*/
		m_Uniforms[name].reset(new UniformValue<GLint,1>(name, (GLint)value));
    }
    // --------------------------------------------------------------------------------------------
    void Material::SetFloat(std::string name, float value)
    {
       /* m_Uniforms[name].Type  = SHADER_TYPE_FLOAT;
        m_Uniforms[name].Float = value;*/
		m_Uniforms[name].reset(new UniformValue<GLfloat,1>(name,(GLfloat) value));

    }
    // --------------------------------------------------------------------------------------------
    void Material::SetTexture(std::string name, Texture* value, unsigned int unit)
    {
        m_SamplerUniforms[name].Unit    = unit;
        m_SamplerUniforms[name].Texture = value;

        switch (value->Target)
        {
        case GL_TEXTURE_1D:
            m_SamplerUniforms[name].Type      = SHADER_TYPE_SAMPLER1D;
            break;
        case GL_TEXTURE_2D:
            m_SamplerUniforms[name].Type      = SHADER_TYPE_SAMPLER2D;
            break;
        case GL_TEXTURE_3D:
            m_SamplerUniforms[name].Type      = SHADER_TYPE_SAMPLER3D;
            break;
        case GL_TEXTURE_CUBE_MAP:
            m_SamplerUniforms[name].Type        = SHADER_TYPE_SAMPLERCUBE;
            break;
        }
        
        if (m_Shader)
        {
            m_Shader->Use();
            m_Shader->SetInt(name, unit);
        }
    }
    // --------------------------------------------------------------------------------------------
    void Material::SetTextureCube(std::string name, TextureCube* value, unsigned int unit)
    {
        m_SamplerUniforms[name].Unit        = unit;
        m_SamplerUniforms[name].Type        = SHADER_TYPE_SAMPLERCUBE;
        m_SamplerUniforms[name].TextureCube = value;

        if (m_Shader)
        {
            m_Shader->Use();
            m_Shader->SetInt(name, unit);
        }
    }
    // ------------------------------------------------------------------------
    void Material::SetVector(std::string name, math::vec2f value)
    {
        /*m_Uniforms[name].Type = SHADER_TYPE_VEC2;
        m_Uniforms[name].Vec2 = value;*/
		m_Uniforms[name].reset(new UniformValue<math::vec2f,1>(name, value));

    }
    // ------------------------------------------------------------------------
    void Material::SetVector(std::string name, math::vec3f value)
    {
       /* m_Uniforms[name].Type = SHADER_TYPE_VEC3;
        m_Uniforms[name].Vec3 = value;*/
		m_Uniforms[name].reset(new UniformValue<math::vec3f,1>(name, value));

    }
    // ------------------------------------------------------------------------
    void Material::SetVector(std::string name, math::vec4f value)
    {
       /* m_Uniforms[name].Type = SHADER_TYPE_VEC4;
        m_Uniforms[name].Vec4 = value;*/
		m_Uniforms[name].reset(new UniformValue<math::vec4f,1>(name, value));

    }
    // ------------------------------------------------------------------------
    void Material::SetMatrix(std::string name, math::mat3f value)
    {
       /* m_Uniforms[name].Type = SHADER_TYPE_MAT3;
        m_Uniforms[name].Mat3 = value;*/
		m_Uniforms[name].reset(new UniformValue<math::mat3f,1>(name, value));

    }
    // ------------------------------------------------------------------------
    void Material::SetMatrix(std::string name, math::mat4f value)
    {
       /* m_Uniforms[name].Type = SHADER_TYPE_MAT4;
        m_Uniforms[name].Mat4 = value;*/
		m_Uniforms[name].reset(new UniformValue<math::mat4f,1>(name, value));

    }
    // ------------------------------------------------------------------------
    std::map<std::string, UniformValueBasePtr>*        Material::GetUniforms()
    {
        return &m_Uniforms;
    }
    // ------------------------------------------------------------------------
    std::map<std::string, UniformValueSampler>* Material::GetSamplerUniforms()
    {
        return &m_SamplerUniforms;
    }
}