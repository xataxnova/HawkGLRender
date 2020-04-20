#pragma once
#include "Camera.h"

class CameraController :public GameElement {
public:
	Camera* bind_cam;
public:
	CameraController(Camera *bind_cam) {
		this->bind_cam = bind_cam;
	}

public://OVERRIDE
	void inputProcess(GLFWwindow *window) {
		Transform &cameraTrans = this->bind_cam->cameraTrans;

		float cameraSpeed = Time::deltaTime * this->bind_cam->cameraMoveSpeed;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraTrans.position += cameraSpeed * this->bind_cam->cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraTrans.position -= cameraSpeed * this->bind_cam->cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraTrans.position -= glm::normalize(glm::cross(this->bind_cam->cameraFront, this->bind_cam->cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraTrans.position += glm::normalize(glm::cross(this->bind_cam->cameraFront, this->bind_cam->cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			cameraTrans.position += cameraSpeed * this->bind_cam->cameraUp;
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			cameraTrans.position -= cameraSpeed * this->bind_cam->cameraUp;
	}
};