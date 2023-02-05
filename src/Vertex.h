#pragma once
#include <glm/glm.hpp>

namespace engine
{
	struct Vertex
	{
		glm::vec3 Position = glm::vec3(0, 0, 0);
		glm::vec3 Normal = glm::vec3(0, 0, 0);
		glm::vec2 UV = glm::vec2(0, 0);

		Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 uv);
		Vertex()
		{

		}
	};
}