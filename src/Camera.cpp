#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace engine
{
	Camera::Camera(float FOV, float aspect, float near, float far)
	{
		mProjection = glm::perspective(FOV, aspect, near, far);
	}

	void Camera::Rotate(float yaw, float pitch)
	{
		glm::vec3 dir;
		dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		dir.y = sin(glm::radians(pitch));
		dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		Direction = glm::normalize(dir);

		mView = glm::lookAt(Position, Position + Direction, Up);
	}

	void Camera::Update()
	{
		mView = glm::lookAt(Position, Position + Direction, Up);
	}
}

