#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Engine.h"

#include "Topics/GLTriangleWithColoredVertex.h"
#include "Topics/GLRectWithTexture.h"
#include "Topics/GLStupidCube.h"

//思考一个问题:编写OpenGL的时候，
// 哪些放在Main函数外部，
// 哪些可以做成外部资源，
// 哪些要写在Main函数内部
// 哪些需要写在主循环里面？
//设置窗口Resize时候的回调函数。
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	// glfw: 初始化OpenGL，选用内核模式的Profile
	// ------------------------------
	if (!glfwInit()) {
		std::cout << "failed to initialize GLFW.\n";
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
	Engine engine;
	engine.warmUp();

	// glfw window creation
	// --------------------
	//GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	//这里应该也把各种句柄什么乱七八糟的windows接口封装了。所以用glfw这种库是正确的
	//，直接用OpenGL接口写东西会生活不能自理的。而且那些玩意，写一遍绝不会写第二遍
	auto window = glfwCreateWindow(
		RenderTarget::mainRenderTarget->Width, 
		RenderTarget::mainRenderTarget->Height, 
		"LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	engine.startUp(window);
	ElementManager *elementMgr = engine.elementManager;
	
	
	auto newElement = new GLStupidCube();	
	newElement->transform.rotation = glm::vec3(15,20,30);	
	elementMgr->addElement(newElement);
	
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{	
		Time::tick();
		cout << "Delta time " << Time::deltaTime << endl;
						
		elementMgr->processInput();
		elementMgr->renderToCamera( Camera::mainCam );

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}