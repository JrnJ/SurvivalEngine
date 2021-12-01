#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float left, float right, float bottom, float top, glm::vec2 position)
	: _projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), _viewMatrix(1.0f), _position(position)
{
	// Set the position
	_viewProjectionMatrix = _projectionMatrix * _viewMatrix;
}

void Camera::SetProjection(float left, float right, float bottom, float top)
{
	_projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	_viewProjectionMatrix = _projectionMatrix * _viewMatrix;
}

void Camera::RecalculateViewMatrix()
{
	/*glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(_position.x, _position.y, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0.0f, 0.0f, 1.0f));

	_viewMatrix = glm::inverse(transform);
	_viewProjectionMatrix = _projectionMatrix * _viewMatrix;*/

	glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -1.0f));
}