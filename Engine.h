#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Common/Common.h"
#include "Managers/Managers.h"

class Engine {
public:
	ElementManager* elementManager;
	GLFWwindow *window = NULL;
public:
	Engine() {}
	~Engine() {}
public:
	void warmUp() {		
		//创建的第一个RenderTarget就是主渲染区域
		RenderTarget::mainRenderTarget = new RenderTarget(0, 0, 1200, 720);
	}

	void startUp( GLFWwindow *win ) {

		this->window = win;

		Input::window = win;

		//设置为鼠标不可控模式，也就是游戏模式。如果是编辑器模式，鼠标还是需要可控的，这个以后再说。
		//这块考虑是不是和Camera结合到一起。
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		//绑定鼠标事件到Input对象中。
		glfwSetCursorPosCallback(window, Input::mouseCallback);
	
		//这里暂时还没做到像Unity的Input一样，将所有事件封装下去。
		elementManager = new ElementManager(win);	

		createDefaultMainCamera();
		createDefaultMainCameraController();
	}

	void tick() {
		Time::tick();
		elementManager->renderToCamera(Camera::mainCam);

		//交换Buffer，拉取事件……忘记干嘛用的了
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();

		//那其实用的是上一帧的数据
		elementManager->update();
		Input::postUpdate();
	}

	void createDefaultMainCamera() {
		Camera::mainCam = new Camera(RenderTarget::mainRenderTarget);
		Camera::mainCam->fov = 45;
		Camera::mainCam->cameraTrans.position = glm::vec3(0.0, 0, -5.0f);				
		elementManager->addElement(Camera::mainCam);
	}

	void createDefaultMainCameraController() {
		FPSCameraController* camCtrl = new FPSCameraController(Camera::mainCam);		
		camCtrl->yaw = 90;
		elementManager->addElement(camCtrl);
	}
};
