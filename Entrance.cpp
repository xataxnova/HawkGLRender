#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Engine.h"

#include "Topics/GLTriangleWithColoredVertex.h"
#include "Topics/GLRectWithTexture.h"
#include "Topics/GLStupidCube.h"

//˼��һ������:��дOpenGL��ʱ��
// ��Щ����Main�����ⲿ��
// ��Щ���������ⲿ��Դ��
// ��ЩҪд��Main�����ڲ�
// ��Щ��Ҫд����ѭ�����棿
//���ô���Resizeʱ��Ļص�������
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	// glfw: ��ʼ��OpenGL��ѡ���ں�ģʽ��Profile
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
	//����Ӧ��Ҳ�Ѹ��־��ʲô���߰����windows�ӿڷ�װ�ˡ�������glfw���ֿ�����ȷ��
	//��ֱ����OpenGL�ӿ�д���������������ġ�������Щ���⣬дһ�������д�ڶ���
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