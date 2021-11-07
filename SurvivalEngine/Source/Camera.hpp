#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

class Camera
{
public:
	// Constrcutor
	Camera(float left, float right, float bottom, float top);

	// Methods
	void SetProjection(float left, float right, float bottom, float top);

	void SetPosition(const glm::vec3& position) 
	{
		_position = position; 
		RecalculateViewMatrix(); 
	}

	// Constant methods
	const glm::vec3& GetPosition() const { return _position; }
	const glm::mat4& GetProjectionMatrix() const { return _projectionMatrix; }
	const glm::mat4& GetViewMatrix() const { return _viewMatrix; }
	const glm::mat4& GetViewProjectionMatrix() const { return _viewProjectionMatrix; }

private:
	// Properties
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
	glm::mat4 _viewProjectionMatrix;

	glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
	float _rotation = 0.0f;

	// Methods
	void RecalculateViewMatrix();
};

#endif