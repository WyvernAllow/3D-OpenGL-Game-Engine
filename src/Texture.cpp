#include "Texture.h"
#include <filesystem>
#include <iostream>

void flip_surface(SDL_Surface* surface)
{
	SDL_LockSurface(surface);

	int pitch = surface->pitch; // row size
	char* temp = new char[pitch]; // intermediate buffer
	char* pixels = (char*)surface->pixels;

	for (int i = 0; i < surface->h / 2; ++i) {
		// get pointers to the two rows to swap
		char* row1 = pixels + i * pitch;
		char* row2 = pixels + (surface->h - i - 1) * pitch;

		// swap rows
		memcpy(temp, row1, pitch);
		memcpy(row1, row2, pitch);
		memcpy(row2, temp, pitch);
	}

	delete[] temp;

	SDL_UnlockSurface(surface);
}


namespace engine
{
	Texture::Texture(const std::string& path)
	{
		if (!std::filesystem::exists(path))
		{
			std::cerr << "Texture at " << path << " does not exist. \n";
		}

		SDL_Surface* surface = SDL_LoadBMP(path.c_str());
		if (!surface)
		{
			std::cerr << "Error loading texture from " << path << "\n";
		}

		flip_surface(surface);

		glGenTextures(1, &mID);
		glBindTexture(GL_TEXTURE_2D, mID);

		GLenum data_fmt;
		Uint8 test = SDL_MapRGB(surface->format, 0xAA, 0xBB, 0xCC) & 0xFF;

		if (test == 0xAA)
		{
			data_fmt = GL_RGB;
		}
		else if (test == 0xCC)
		{
			data_fmt = GL_BGR;
		}
		else 
		{
			printf("Error: \"Loaded surface was neither RGB or BGR!\""); return;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, data_fmt, GL_UNSIGNED_BYTE, surface->pixels);

		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		float aniso = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &mID);
	}

	void Texture::UseTextureUnit(GLuint unit) const
	{
		glBindTexture(GL_TEXTURE_2D, mID);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, mID);
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}