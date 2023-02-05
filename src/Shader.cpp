#include "Shader.h"
#include "utils/utils.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace engine
{
	Shader::Shader(const std::string& vertPath, const std::string& fragPath)
	{
		std::string vertShaderSource = utils::ReadText(vertPath);
		std::string fragShaderSource = utils::ReadText(fragPath);

		GLuint vertShader = CompileShader(vertShaderSource.c_str(), GL_VERTEX_SHADER);
		GLuint fragShader = CompileShader(fragShaderSource.c_str(), GL_FRAGMENT_SHADER);

		mID = glCreateProgram();
		glAttachShader(mID, vertShader);
		glAttachShader(mID, fragShader);
		glLinkProgram(mID);
		
		// Error checking.
		GLint isLinked;
		glGetProgramiv(mID, GL_LINK_STATUS, &isLinked);
		if (!isLinked)
		{
			char infoLog[1024];
			glGetProgramInfoLog(mID, 1024, nullptr, infoLog);

			std::cerr << infoLog << "\n";
		}

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(mID);
	}

	void Shader::Bind() const
	{
		glUseProgram(mID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::SetUniformMat4(const std::string& location, glm::mat4 value) const
	{
		int modelLoc = glGetUniformLocation(mID, location.c_str());
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::SetUniformVec3(const std::string& name, glm::vec3 value) const
	{
		int modelLoc = glGetUniformLocation(mID, name.c_str());
		glUniform3fv(modelLoc, 1, glm::value_ptr(value));
	}

	void Shader::SetSamplerTextureUnit(const std::string& samplerName, GLuint textureUnit) const
	{
		int modelLoc = glGetUniformLocation(mID, samplerName.c_str());
		glUniform1i(modelLoc, textureUnit);
	}

	GLuint Shader::CompileShader(const char* source, GLenum type)
	{
		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		// Error checking.
		GLint isCompiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (!isCompiled)
		{
			char infoLog[1024];
			glGetShaderInfoLog(shader, 1024, nullptr, infoLog);

			std::cerr << infoLog << "\n";
		}

		return shader;
	}
}
