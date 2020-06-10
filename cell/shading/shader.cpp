#include "shader.h"

#include <utility/logging/log.h>

#include "../glad/glad.h"

#include <fstream>
#include <string>

namespace Cell
{
    // --------------------------------------------------------------------------------------------
    Shader::Shader()
    {

    }
    // --------------------------------------------------------------------------------------------
    Shader::Shader(std::string name, std::string vsCode, std::string fsCode, std::vector<std::string> defines)
    {      
        Load(name, vsCode, fsCode, defines);
    }
    // --------------------------------------------------------------------------------------------
    void Shader::Load(std::string name, std::string vsCode, std::string fsCode, std::vector<std::string> defines)
    {
        Name = name;
        // compile both shaders and link them
        unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
        ID = glCreateProgram();
        int status;
        char log[1024];

        // if a list of define statements is specified, add these  to the start of the shader 
        // source, s.t. we can selectively compile different shaders based on the defines we set.
		std::string vs_final_code;
		std::string fs_final_code;
        if (defines.size() > 0)
        {
            std::vector<std::string> vsMergedCode;
            std::vector<std::string> fsMergedCode;
            // first determine if the user supplied a #version  directive at the top of the shader 
            // code, in which case we  extract it and add it 'before' the list of define code.
            // the GLSL version specifier is only valid as the first line of the GLSL code; 
            // otherwise the GLSL version defaults to 1.1.
            std::string firstLine = vsCode.substr(0, vsCode.find("\n"));
            if (firstLine.find("#version") != std::string::npos)
            {
                // strip shader code of first line and add to list of shader code strings.
                vsCode = vsCode.substr(vsCode.find("\n") + 1, vsCode.length() - 1);
                vsMergedCode.push_back(firstLine + "\n");
            }
            firstLine = fsCode.substr(0, fsCode.find("\n"));
            if (firstLine.find("#version") != std::string::npos)
            {
                // strip shader code of first line and add to list of shader code strings.
                fsCode = fsCode.substr(fsCode.find("\n") + 1, fsCode.length() - 1);
                fsMergedCode.push_back(firstLine + "\n");
            }
            // then add define statements to the shader string list.
            for (unsigned int i = 0; i < defines.size(); ++i)
            {
                std::string define = "#define " + defines[i] + "\n";
                vsMergedCode.push_back(define);
                fsMergedCode.push_back(define);
            }
            // then addremaining shader code to merged result and pass result to glShaderSource.
            vsMergedCode.push_back(vsCode);
            fsMergedCode.push_back(fsCode);
            // note that we manually build an array of C style  strings as glShaderSource doesn't 
            // expect it in any other format.
            // all strings are null-terminated so pass NULL as glShaderSource's final argument.
            const char **vsStringsC = new const char*[vsMergedCode.size()];
            const char **fsStringsC = new const char*[fsMergedCode.size()];
			for (unsigned int i = 0; i < vsMergedCode.size(); ++i)
			{
				vsStringsC[i] = vsMergedCode[i].c_str();
				vs_final_code += vsMergedCode[i];
			}
			for (unsigned int i = 0; i < fsMergedCode.size(); ++i)
			{
				fsStringsC[i] = fsMergedCode[i].c_str();
				fs_final_code += fsMergedCode[i];
			}
            glShaderSource(vs, vsMergedCode.size(), vsStringsC, NULL);
            glShaderSource(fs, fsMergedCode.size(), fsStringsC, NULL);
			
            delete[] vsStringsC;
            delete[] fsStringsC;
        }
        else
        {
            const char *vsSourceC = vsCode.c_str();
            const char *fsSourceC = fsCode.c_str();
            glShaderSource(vs, 1, &vsSourceC, NULL);
            glShaderSource(fs, 1, &fsSourceC, NULL);
			vs_final_code = vsCode;
			fs_final_code = fsCode;
        }
        glCompileShader(vs);
        glCompileShader(fs);

        glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            glGetShaderInfoLog(vs, 1024, NULL, log);
            Log::Message("Vertex shader compilation error at: " + name + "!\n" + std::string(log), LOG_ERROR);
			std::string fileName = name + "_vs.glsl";
			std::ofstream OsWrite(fileName, std::ostream::app);
			OsWrite << fs_final_code;
			OsWrite << std::endl;
			OsWrite.close();
        }
        glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            glGetShaderInfoLog(fs, 1024, NULL, log);
            Log::Message("Fragment shader compilation error at: " + name + "!\n" + std::string(log), LOG_ERROR);
			std::string fileName = name + "_fg.glsl";
			std::ofstream OsWrite(fileName, std::ostream::app);
			OsWrite <<fs_final_code;
			OsWrite << std::endl;
			OsWrite.close();
        }

        glAttachShader(ID, vs);
        glAttachShader(ID, fs);
        glLinkProgram(ID);

        glGetProgramiv(ID, GL_LINK_STATUS, &status);
        if (!status)
        {
            glGetProgramInfoLog(ID, 1024, NULL, log);
            Log::Message("Shader program linking error: \n" + std::string(log), LOG_ERROR);
        }

        glDeleteShader(vs);
        glDeleteShader(fs);

        // query the number of active uniforms and attributes
        int nrAttributes, nrUniforms;
        glGetProgramiv(ID, GL_ACTIVE_ATTRIBUTES, &nrAttributes);
        glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &nrUniforms);
        Attributes.resize(nrAttributes);
        Uniforms.resize(nrUniforms);

        // iterate over all active attributes
        char buffer[128];
        for (unsigned int i = 0; i < nrAttributes; ++i)
        {
            GLenum glType;
            glGetActiveAttrib(ID, i, sizeof(buffer), 0, &Attributes[i].Size, &glType, buffer);
            Attributes[i].Name = std::string(buffer);
            Attributes[i].Type = SHADER_TYPE_BOOL; 

            Attributes[i].Location = glGetAttribLocation(ID, buffer);
        }

        // iterate over all active uniforms
        for (unsigned int i = 0; i < nrUniforms; ++i)
        {
            GLenum glType;
            glGetActiveUniform(ID, i, sizeof(buffer), 0, &Uniforms[i].Size, &glType, buffer);
            Uniforms[i].Name = std::string(buffer);
			switch (glType)
			{
			case GL_FLOAT:
				Uniforms[i].Type = SHADER_TYPE_FLOAT;
				break;
			case GL_INT:
				Uniforms[i].Type = SHADER_TYPE_INT;
				break;
			case GL_BOOL:
				Uniforms[i].Type = SHADER_TYPE_BOOL;
				break;
			case GL_FLOAT_VEC2:
				Uniforms[i].Type = SHADER_TYPE_VEC2;
				break;
			case GL_FLOAT_VEC3:
				Uniforms[i].Type = SHADER_TYPE_VEC3;
				break;
			case GL_FLOAT_VEC4:
				Uniforms[i].Type = SHADER_TYPE_VEC4;
				break;
			case GL_SAMPLER_2D:
				Uniforms[i].Type = SHADER_TYPE_SAMPLER2D;
				break;
			case GL_SAMPLER_CUBE:
				Uniforms[i].Type = SHADER_TYPE_SAMPLERCUBE;
				break;
			case GL_FLOAT_MAT3:
				Uniforms[i].Type = SHADER_TYPE_MAT3;
				break;
			case GL_FLOAT_MAT4:
				Uniforms[i].Type = SHADER_TYPE_MAT4;
				break;
			default:
				Uniforms[i].Type = SHADER_TYPE_BOOL;
				break;
			}

            Uniforms[i].Location = glGetUniformLocation(ID, buffer);
        }
    }
    // --------------------------------------------------------------------------------------------
    void Shader::Use()
    {
        glUseProgram(ID);
    }
    // --------------------------------------------------------------------------------------------
    bool Shader::HasUniform(std::string name)
    {
        for (unsigned int i = 0; i < Uniforms.size(); ++i)
        {
            if(Uniforms[i].Name == name)
                return true;
        }
        return false;
    }
    // --------------------------------------------------------------------------------------------
    void Shader::SetInt(std::string location, int value)
    {
        int loc = getUniformLocation(location);
        if (loc >= 0)
            glUniform1i(loc, value);
    }
    // --------------------------------------------------------------------------------------------
    void Shader::SetBool(std::string location, bool value)
    {
        int loc = getUniformLocation(location);
        if (loc >= 0)
            glUniform1i(loc, (int)value);
    }
    // --------------------------------------------------------------------------------------------
    void Shader::SetFloat(std::string location, float value)
    {
        int loc = getUniformLocation(location);
        if (loc >= 0)
            glUniform1f(loc, value);
    }
	void Shader::SetFloatArray(std::string location, const std::vector<float>& floatArray)
	{
		int loc = glGetUniformLocation(ID, (GLchar*)location.c_str());

		//int loc = getUniformLocation(location);
		if (loc >= 0)
			glUniform4fv(loc, (GLsizei)(floatArray.size() / 4), floatArray.data());
	}
    // --------------------------------------------------------------------------------------------
    void Shader::SetVector(std::string location, math::vec2f value)
    {
        int loc = getUniformLocation(location);
        if (loc >= 0)
            glUniform2fv(loc, 1, &value[0]);        
    }
    // --------------------------------------------------------------------------------------------
    void Shader::SetVector(std::string location, math::vec3f value)
    {
        int loc = getUniformLocation(location);
        if (loc >= 0)
            glUniform3fv(loc, 1, &value[0]);
    }
    // --------------------------------------------------------------------------------------------
    void Shader::SetVector(std::string location, math::vec4f value)
    {
        int loc = getUniformLocation(location);
        if (loc >= 0)
            glUniform4fv(loc, 1, &value[0]);
    }
    // --------------------------------------------------------------------------------------------
    void Shader::SetVectorArray(std::string location, int size, const std::vector<math::vec2f>& values)
    {
        unsigned int loc = glGetUniformLocation(ID, location.c_str());
        if (loc >= 0)
        {
            glUniform2fv(loc, size, (float*)(&values[0].x));
        }
    }
    // --------------------------------------------------------------------------------------------
    void Shader::SetVectorArray(std::string location, int size, const std::vector<math::vec3f>& values)
    {
        unsigned int loc = glGetUniformLocation(ID, location.c_str());
        if (loc >= 0)
        {
            glUniform3fv(loc, size, (float*)(&values[0].x));
        }
    }
    // --------------------------------------------------------------------------------------------
    void Shader::SetVectorArray(std::string location, int size, const std::vector<math::vec4f>& values)
    {
        unsigned int loc = glGetUniformLocation(ID, location.c_str());
        if (loc >= 0)
        {
            glUniform4fv(loc, size, (float*)(&values[0].x));
        }
    }
    // --------------------------------------------------------------------------------------------
   /* void Shader::SetMatrix(std::string location, math::mat2 value)
    {
        int loc = getUniformLocation(location);
        if (loc >= 0)
            glUniformMatrix2fv(loc, 1, GL_FALSE, &value[0][0]);
    }*/
    // --------------------------------------------------------------------------------------------
    void Shader::SetMatrix(std::string location, math::mat3f value)
    {
        int loc = getUniformLocation(location);
        if (loc >= 0)
			glUniformMatrix3fv(loc, 1, GL_FALSE, value);

            //glUniformMatrix3fv(loc, 1, GL_FALSE, &value[0][0]);
    }
    // --------------------------------------------------------------------------------------------
    void Shader::SetMatrix(std::string location, math::mat4f value)
    {
        int loc = getUniformLocation(location);
        if (loc >= 0)
            glUniformMatrix4fv(loc, 1, GL_FALSE, value);
			//glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
	}
    // --------------------------------------------------------------------------------------------
    int Shader::getUniformLocation(std::string name)
    {
        // read from uniform/attribute array as originally obtained from OpenGL
        for (unsigned int i = 0; i < Uniforms.size(); ++i)
        {
            if(Uniforms[i].Name == name)
                return Uniforms[i].Location;
        }
        return -1;
    }
	GLint Shader::GetUnifomLocation(const GLchar * uniformName)
	{
		return glGetUniformLocation(ID, uniformName);
	}
	bool Shader::SetUniform1f(const GLchar * uniformName, GLfloat value, GLint & location)
	{
		if (location == -1) {
			location = glGetUniformLocation(ID, uniformName);
			if (location != -1) {
				glUniform1f(location, value);
				return true;
			}
			else return false;
		}
		else {
			glUniform1f(location, value);
			return true;
		}
	}
	bool Shader::SetUniform1f(GLint location, GLfloat value)
	{
		if (location != -1) {
			glUniform1f(location, value);
			return true;
		}
		return false;
	}
	bool Shader::SetUniform1i(const GLchar * uniformName, GLint value, GLint & location)
	{
		if (location == -1) {
			location = glGetUniformLocation(ID, uniformName);
			if (location != -1) {
				glUniform1i(location, value);
				return true;
			}
			else { return false; }
		}
		else {
			glUniform1i(location, value);
			return true;
		}
	}
	bool Shader::SetUniform2fv(const GLchar * uniformName, GLsizei count, const GLfloat * value, GLint & location)
	{
		if (location == -1) {
			location = glGetUniformLocation(ID, uniformName);
			if (location != -1) {
				glUniform2fv(location, count, value);
				return true;
			}
			else return false;
		}
		else {
			glUniform2fv(location, count, value);
			return true;
		}
	}
	bool Shader::SetUniform2fv(GLint location, GLsizei count, const GLfloat * value)
	{
		if (location != -1) {
			glUniform2fv(location, count, value);
			return true;
		}
		return false;
	}
	bool Shader::SetUniform3fv(const GLchar * uniformName, GLsizei count, const GLfloat * value, GLint & location)
	{
		if (location == -1) {
			location = glGetUniformLocation(ID, uniformName);
			if (location != -1) {
				glUniform3fv(location, count, value);
				return true;
			}
			else return false;
		}
		else {
			glUniform3fv(location, count, value);
			return true;
		}
	}
	bool Shader::SetUniform4fv(const GLchar * uniformName, GLsizei count, const GLfloat * value, GLint & location)
	{
		if (location == -1) {
			location = glGetUniformLocation(ID, uniformName);
			if (location != -1) {
				glUniform4fv(location, count, value);
				return true;
			}
			else { return false; }
		}
		else {
			glUniform4fv(location, count, value);
			return true;
		}
	}
	bool Shader::SetUniform4fv(GLint location, GLsizei count, const GLfloat * value)
	{
		if (location != -1) {
			glUniform4fv(location, count, value);
			return true;
		} return false;
	}
	bool Shader::SetUniformMatrix4x4fv(const GLchar * uniformName, GLsizei count, GLboolean transpose, const GLfloat * value, GLint & location)
	{
		if (location == -1) {
			location = glGetUniformLocation(ID, uniformName);
			if (location != -1) {
				glUniformMatrix4fv(location, count, transpose, value);
				return true;
			}
			else return false;
		}
		else {
			glUniformMatrix4fv(location, count, transpose, value);
			return true;
		}
	}
	bool Shader::SetUniformMatrix3x3fv(const GLchar * uniformName, GLsizei count, GLboolean transpose, const GLfloat * value, GLint & location)
	{
		if (location == -1) {
			location = glGetUniformLocation(ID, uniformName);
			if (location != -1) {
				glUniformMatrix3fv(location, count, transpose, value);
				return true;
			}
			else return false;
		}
		else {
			glUniformMatrix3fv(location, count, transpose, value);
			return true;
		}
	}
}