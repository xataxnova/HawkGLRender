#pragma once
#include <GLFW/glfw3.h>
#include "RenderTarget.h"

class Input {
public:
	static double x;
	static double y;
	static double delta_x;
	static double delta_y;
	static bool firstRun;
	static GLFWwindow *window;
public:
	static bool isKeyDown( int key) {
		return glfwGetKey(window, key) == GLFW_PRESS;
	}
	
	static bool isKeyUp( int key ) {
		return glfwGetKey(window, key) == GLFW_RELEASE;
	}

	static void setInitValue( RenderTarget * renderTarget, GLFWwindow *in_win) {
		window = in_win;

		x = renderTarget->Width / 2;
		y = renderTarget->Height / 2;
		delta_x = 0;
		delta_y = 0;
	}

	static void mouseCallback(GLFWwindow * window, double x_pos, double y_pos) {
		if (firstRun) {
			x = x_pos;
			y = y_pos;
			firstRun = false;
		}

		delta_x = x_pos - x;
		delta_y = y_pos - y;
		x = x_pos;
		y = y_pos;
	}

	static void postUpdate() {
		delta_x = 0;
		delta_y = 0;
	}
};

double Input::x = 0;
double Input::y = 0;
double Input::delta_x = 0;
double Input::delta_y = 0;
bool Input::firstRun = true;
GLFWwindow* Input::window = NULL;