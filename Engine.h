#pragma once
#include "Common/Common.h"
#include "Managers/Managers.h"

class Engine {
public:
	ElementManager* elementManager;
public:
	Engine() {}
	~Engine() {}
public:
	void warmUp() {
		//创建的第一个RenderTarget就是
		RenderTarget::mainRenderTarget = new RenderTarget(0, 0, 1200, 720);
	}

	void startUp( GLFWwindow *win ) {
		elementManager = new ElementManager(win);	

		createDefaultMainCamera();
		createDefaultMainCameraController();
	}

	void createDefaultMainCamera() {
		Camera::mainCam = new Camera(RenderTarget::mainRenderTarget);
		Camera::mainCam->fov = 45;
		//当使用View矩阵的时候，不再需要将Camera以相反方向运动了！否则Camera的位置是反的。
		//假设被观察物体，在原点。
		//Unity是左手坐标系，-Z朝着屏幕外面，所以摄影机设置成-5位置，向着（0，0，1）方向看。
		//OpenGL，Z朝着屏幕外卖，所以摄影机设置为5，朝着（0，0，-1）方向看。
		Camera::mainCam->cameraTrans.position = glm::vec3(0, 0, 5.0f);

		elementManager->addElement(Camera::mainCam);
	}

	void createDefaultMainCameraController() {
		CameraController* camCtrl = new CameraController(Camera::mainCam);

		elementManager->addElement(camCtrl);
	}
};
