#pragma once
#include <glm/glm.hpp>

namespace engine
{
	class Camera
	{
	public:
		glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
		Camera(float FOV, float aspect, float near, float far);
		
		glm::mat4 GetViewProjectionMatrix() const { return mProjection * mView; }

		void Rotate(float yaw, float pitch);

		glm::vec3 GetRight() { return glm::normalize(glm::cross(Direction, Up)); }
		glm::vec3 GetDirection() { return Direction; }

		void Update();

	private:


	private:

		glm::vec3 Direction = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Right = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 mView;
		glm::mat4 mProjection;
	};
}