#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	// Constructor
	Camera(float left, float right, float bottom, float top);

	// Position
	const glm::vec2& GetPosition() const { return _position; }
	void SetPosition(const glm::vec2 position) { _position = position; RecalculateViewMatrix(); }

	// Rotation
	const float GetRotation() const { return _rotation; }
	void SetRotation(const float rotation) { _rotation = rotation; RecalculateViewMatrix(); }

	// Zoom
	const float GetZoom() const { return _zoom; }
	void SetZoom(const float zoom) { _zoom = zoom; RecalculateViewMatrix(); }

	// ProjectionMatrix
	const glm::mat4 GetProjectionMatrix() const { return _projectionMatrix; }
	void SetProjectionMatrix(float left, float right, float bottom, float top) 
	{ 
		_projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f); 
		RecalculateViewMatrix(); 
	}

	const glm::mat4 GetViewMatrix() const { return _viewMatrix; }
	const glm::mat4 GetViewProjectionMatrix() const { return _viewProjectionMatrix; }

private:
	// Properties
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
	glm::mat4 _zoomMatrix;
	glm::mat4 _viewProjectionMatrix;
	glm::vec2 _position = { 0.0f, 0.0f };
	float _rotation = 0.0f;
	float _zoom = 1.0f;

	//
	void RecalculateViewMatrix();
};

#endif