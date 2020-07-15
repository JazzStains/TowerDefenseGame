#include "camera2D.h"

namespace GameEngine {
	camera2D::camera2D() : _position(0.0f, 0.0f),
		_cameraMatrix(1.0f),
		_orthoMatrix(1.0f),
		_scale(1.0f),
		_needsMatrixUpdate(true),
		_screenWidth(500),
		_screenHeight(500)
	{

	}

	camera2D::~camera2D() {

	}

	void camera2D::update() {
		if (_needsMatrixUpdate) {
			//camera translation
			glm::vec3 translate(-_position.x,-_position.y, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			//camera scale
			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale)*_cameraMatrix;
			_needsMatrixUpdate = false;
		}
	}
	void camera2D::init(int screenWidth, int screenHeight) {
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}

	glm::vec2 camera2D::convertScreenToWorld(glm::vec2 screenCoords) {
		screenCoords.y =  _screenHeight - screenCoords.y;
		return screenCoords;
	}
}