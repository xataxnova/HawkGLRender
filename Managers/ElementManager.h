#pragma once
#include "RenderManager.h"
#include <vector>
#include "../Common/Common.h"


class ElementManager{
public:
	RenderManager *renderManager = NULL;
	GLFWwindow *window = NULL;
	vector<GameElement*> elements;
public:
	ElementManager( GLFWwindow *win ) {
		this->window = win;
		renderManager = new RenderManager();
	}	

	void addElement(GameElement* new_element) {
		elements.push_back(new_element);

		GLRenderElement* render_element = dynamic_cast<GLRenderElement*>(new_element);
		if (render_element != NULL) {
			renderManager->addRenderElement(render_element);			
		}
	}

	void renderToCamera(Camera* cam) {
		renderManager->renderToCamera(cam);
	}

	void processInput() {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		for (size_t i = 0; i < elements.size(); i++)
		{
			elements[i]->inputProcess(window);
		}
	}
};