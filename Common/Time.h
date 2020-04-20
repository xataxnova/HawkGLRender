#pragma once
#include <GLFW/glfw3.h>

class Time {
private:
	static float timeLastFrame;
public:
	static float deltaTime;
	static float timeSinceStartup;
	static void tick() {
		timeSinceStartup = (float)glfwGetTime();
		deltaTime = timeSinceStartup - timeLastFrame;
		timeLastFrame = timeSinceStartup;
	}
};

float Time::timeSinceStartup = 0;
float Time::timeLastFrame = 0;
float Time::deltaTime = 0;
