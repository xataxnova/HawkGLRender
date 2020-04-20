#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector> 
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Transform.h"
#include "RenderTarget.h"
#include "Time.h"
#include "GameElement.h"

class Camera : public GameElement {
private:
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;	
public://components
	Transform cameraTrans;
	Transform *lookAtTarget;
	RenderTarget *renderTarget;
	static Camera * mainCam;
public://veriables	
	float fov;
	float farPlane;
	float nearPlane;	
	float cameraMoveSpeed = 2.0f;

	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
public://functions
	Camera( RenderTarget * renderTarget):
		model( glm::mat4(1.0f) ),
		view( glm::mat4(1.0f) ),
		projection( glm::mat4(1.0f)),
		fov(45.0f),
		farPlane(100.0f),
		nearPlane(0.01f)
	{
		this->renderTarget = renderTarget;
	}

	void doModel( Transform& trans ) {
		model = Transform::identity;
		trans.doLocal(model);
		//model = glm::rotate(model, glm::radians(cameraTrans.rotation.x), Transform::axis_x);
		//model = glm::rotate(model, glm::radians(cameraTrans.rotation.y), Transform::axis_y);
		//model = glm::rotate(model, glm::radians(cameraTrans.rotation.z), Transform::axis_z);
	}

	void doView() {
		view = glm::lookAt(cameraTrans.position, cameraTrans.position + cameraFront, cameraUp);
	}

	void doProjection() {
		projection = Transform::identity;
		projection = glm::perspective(glm::radians(fov), renderTarget->displayRatio, nearPlane, farPlane);
	}

	void applyMVP(Shader * shader, Transform& trans) {
		doModel( trans );
		doView();
		doProjection();
		shader->setMatrix4fv("model", model);
		shader->setMatrix4fv("view", view);
		shader->setMatrix4fv("projection", projection);
	}

	//这个做法不太好，这个不是Camera的功能，而是FirstPersonController的功能。等做完这个例子之后，把他抽出来。
	//作为一个CameraController类来操作！
	//Transfrom追加 getUp，getRight，getForward三个关联方法。
	void processInput(GLFWwindow *window)
	{

	}
};

Camera* Camera::mainCam = NULL;

