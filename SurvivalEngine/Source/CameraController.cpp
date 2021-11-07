#include "CameraController.hpp"

CameraController::CameraController(float aspectRatio, bool rotation)
	: _aspectRatio(aspectRatio), _camera(0, 0, 0, 0), _rotation(rotation)
{

}