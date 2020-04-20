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
		//�����ĵ�һ��RenderTarget����
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
		//��ʹ��View�����ʱ�򣬲�����Ҫ��Camera���෴�����˶��ˣ�����Camera��λ���Ƿ��ġ�
		//���豻�۲����壬��ԭ�㡣
		//Unity����������ϵ��-Z������Ļ���棬������Ӱ�����ó�-5λ�ã����ţ�0��0��1�����򿴡�
		//OpenGL��Z������Ļ������������Ӱ������Ϊ5�����ţ�0��0��-1�����򿴡�
		Camera::mainCam->cameraTrans.position = glm::vec3(0, 0, 5.0f);

		elementManager->addElement(Camera::mainCam);
	}

	void createDefaultMainCameraController() {
		CameraController* camCtrl = new CameraController(Camera::mainCam);

		elementManager->addElement(camCtrl);
	}
};
