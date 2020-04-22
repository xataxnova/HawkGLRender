#pragma once
#include <iostream>
#include "Camera.h"
#include "Input.h"

class FPSCameraController :public GameElement {
public:
	Camera* bind_cam;
	float sensitivity = 0.05f;
	float yaw;
	float pitch;
public:
	FPSCameraController(Camera *bind_cam) {
		this->bind_cam = bind_cam;
	}

public://OVERRIDE
	void update() {
		Transform &cameraTrans = this->bind_cam->cameraTrans;

		float cameraSpeed = Time::deltaTime * this->bind_cam->cameraMoveSpeed;
		if ( Input::isKeyDown( GLFW_KEY_W ) )
			cameraTrans.position += cameraSpeed * this->bind_cam->cameraFront;
		if ( Input::isKeyDown( GLFW_KEY_S ) )
			cameraTrans.position -= cameraSpeed * this->bind_cam->cameraFront;
		if ( Input::isKeyDown( GLFW_KEY_A ) )
			cameraTrans.position -= glm::normalize(glm::cross(this->bind_cam->cameraFront, this->bind_cam->cameraUp)) * cameraSpeed;
		if ( Input::isKeyDown( GLFW_KEY_D ) )
			cameraTrans.position += glm::normalize(glm::cross(this->bind_cam->cameraFront, this->bind_cam->cameraUp)) * cameraSpeed;
		if ( Input::isKeyDown( GLFW_KEY_Q ) )
			cameraTrans.position += cameraSpeed * this->bind_cam->cameraUp;
		if ( Input::isKeyDown( GLFW_KEY_E ) )
			cameraTrans.position -= cameraSpeed * this->bind_cam->cameraUp;		

		updateLookAt();
	}
private:
	void updateLookAt(){
		float x_offset = this->sensitivity * Input::delta_x;
		float y_offset = this->sensitivity * Input::delta_y;
		
		yaw += x_offset;
		pitch -= y_offset;

		if (pitch > 89.0f) {
			pitch = 89.0f;
		}

		if (pitch < -89.0f) {
			pitch = -89.0f;
		}

		this->bind_cam->cameraFront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		this->bind_cam->cameraFront.y = sin(glm::radians(pitch));
		this->bind_cam->cameraFront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		this->bind_cam->cameraFront = glm::normalize( this->bind_cam->cameraFront);
	} 
};