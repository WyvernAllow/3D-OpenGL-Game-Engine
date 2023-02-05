#pragma once
#include <glad/glad.h>
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

namespace engine
{
	class Renderer
	{
	public:
		Renderer(Camera& camera, Shader& shader);

		void Begin(Shader& shader);
		void Draw(const Mesh& mesh, const Texture& texture, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
		void End();

	private:
		Camera& mActiveCamera;
		Shader& mShader;
	};
}