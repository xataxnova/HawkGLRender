#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GameElement {
public:
	virtual void inputProcess( GLFWwindow *win ) {}
};