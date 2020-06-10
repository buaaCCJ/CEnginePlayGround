#ifndef CELL_SHADING_SHADER_H
#define CELL_SHADING_SHADER_H

#include <string>
#include <vector>

#include <math/linear_algebra/vmath.h>
#include<math.h>
#include "shading_types.h"
namespace Cell
{
    /* 

      Shader object for quickly creating and using a GPU shader object. When compiling/linking a 
      shader object from source code, all vertex attributes and uniforms are extracted for saving
      unnecessary additional CPU->GPU roundtrip times.
	class 
    */

    class Shader
    {
    public:
        unsigned int ID;
        std::string  Name;

        std::vector<Uniform>         Uniforms;
        std::vector<VertexAttribute> Attributes;

    public:
        Shader();
        Shader(std::string name, std::string vsCode, std::string fsCode, std::vector<std::string> defines = std::vector<std::string>());

        void Load(std::string name, std::string vsCode, std::string fsCode, std::vector<std::string> defines = std::vector<std::string>());

        void Use();

        bool HasUniform(std::string name);

        void SetInt   (std::string location, int   value);
        void SetBool  (std::string location, bool  value);
        void SetFloat (std::string location, float value);
		void SetFloatArray(std::string location, const std::vector<float>& floatArray);
        void SetVector(std::string location, math::vec2f  value);
        void SetVector(std::string location, math::vec3f  value);
        void SetVector(std::string location, math::vec4f  value);
        void SetVectorArray(std::string location, int size, const std::vector<math::vec2f>& values);
        void SetVectorArray(std::string location, int size, const std::vector<math::vec3f>& values);
        void SetVectorArray(std::string location, int size, const std::vector<math::vec4f>& values);
        //void SetMatrix(std::string location, math::mat2 value);
        void SetMatrix(std::string location, math::mat3f value);
        void SetMatrix(std::string location, math::mat4f value);
       // void SetMatrixArray(std::string location, int size, math::mat2* values);
        void SetMatrixArray(std::string location, int size, math::mat3f* values);
        void SetMatrixArray(std::string location, int size, math::mat4f* values);

		GLint GetUnifomLocation(const GLchar* uniformName);
		bool SetUniform1f(const GLchar* uniformName, GLfloat value, GLint& location);
		bool SetUniform1f(GLint location, GLfloat value);
		bool SetUniform1i(const GLchar* uniformName, GLint value, GLint& location);
		bool SetUniform2fv(const GLchar* uniformName, GLsizei count, const GLfloat* value, GLint& location);
		bool SetUniform2fv(GLint location, GLsizei count, const GLfloat* value);
		bool SetUniform3fv(const GLchar* uniformName, GLsizei count, const GLfloat* value, GLint& location);
		bool SetUniform4fv(const GLchar* uniformName, GLsizei count, const GLfloat* value, GLint& location);
		bool SetUniform4fv(GLint location, GLsizei count, const GLfloat* value);
		bool SetUniformMatrix4x4fv(const GLchar* uniformName, GLsizei count, GLboolean transpose, const GLfloat* value, GLint& location);
		bool SetUniformMatrix3x3fv(const GLchar* uniformName, GLsizei count, GLboolean transpose, const GLfloat* value, GLint& location);

    private:
        // retrieves uniform location from pre-stored uniform locations and reports an error if a 
        // non-uniform is set.
        int getUniformLocation(std::string name);
    };
}
#endif