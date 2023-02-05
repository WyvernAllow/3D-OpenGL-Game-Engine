#pragma once
#include "Vertex.h"
#include <glad/glad.h>
#include <vector>
#include <string>

namespace engine
{
	class Mesh
	{
	public:
		Mesh(const std::string& path);
		~Mesh();

		void Bind() const;
		void Unbind() const;

		int GetIndexCount() const { return mIndexCount; }

	private:
		GLuint mVAO;
		GLuint mVBO;
		GLuint mEBO;

		int mIndexCount;
	};
}