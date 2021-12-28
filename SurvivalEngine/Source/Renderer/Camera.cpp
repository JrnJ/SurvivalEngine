#include "Camera.hpp"
#include "../Math.hpp"

Camera::Camera(float left, float right, float bottom, float top)
	: _projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), _viewMatrix(1.0f)
{
	_viewProjectionMatrix = _projectionMatrix * _viewMatrix;
}

void Camera::RecalculateViewMatrix()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position) *
		glm::rotate(glm::mat4(1.0f), Math::RadToDeg(_rotation), glm::vec3(0.0f, 0.0f, 1.0f));

	//glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position) *
	//	glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0.0f, 0.0f, 1.0f));

	// Set and Invert ViewMatrix
	_viewMatrix = glm::inverse(transform);
	_viewProjectionMatrix = _projectionMatrix * _viewMatrix;
}
