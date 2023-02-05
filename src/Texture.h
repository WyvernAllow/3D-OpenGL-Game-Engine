#pragma once
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <string>

namespace engine
{
	class Texture
	{
	public:
		Texture(const std::string& path);
		~Texture();

		void UseTextureUnit(GLuint unit) const;

		void Bind() const;
		void Unbind() const;

	private:
		GLuint mID;
	};
}