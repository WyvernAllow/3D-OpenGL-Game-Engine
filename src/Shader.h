#pragma once
#include "utils/Utils.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace engine
{
	class Shader
	{
	public:
		Shader(const std::string& vertPath, const std::string& fragPath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniformMat4(const std::string& name, glm::mat4 value) const;
		void SetUniformVec3(const std::string& name, glm::vec3 value) const;
		void SetSamplerTextureUnit(const std::string& samplerName, GLuint textureUnit) const;

	private:
		GLuint CompileShader(const char* source, GLenum type);

	private:
		GLuint mID;
	};
}