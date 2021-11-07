#ifndef CAMERACONTROLLER_HPP
#define CAMERACONTROLLER_HPP

#include "Camera.hpp"

class CameraController
{
public:
	// Properties
	glm::vec3 Position = { 0.0f, 0.0f, 0.0f };

	// Constructors
	CameraController(float aspectRatio, bool rotation = false);

	// Methods
	//void OnUpdate();
	//void OnEvent();
	Camera& GetCamera() { return _camera; }
	const Camera& GetCamera() const { return _camera; }

	float GetZoomLevel() const { return _zoomLevel; }
	void SetZoomLevel(float level) { _zoomLevel = level; }

private:
	// Properties
	float _aspectRatio;
	float _zoomLevel = 1.0f;
	Camera _camera;

	bool _rotation;

	float _cameraRotation = 0.0f; // Degrees, Anti-clockwise
	float _cCameraTranslationSpeed = 5.0f;
	float _cameraRotationSpeed = 180.0f;
};

#endif