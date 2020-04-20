#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector> 
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class Transform {
public:
	static glm::vec3 axis_x;
	static glm::vec3 axis_y;
	static glm::vec3 axis_z;	
	static glm::mat4 identity;
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
public:
	Transform():
		position(glm::vec3( 0.0f,0.0f,0.0f )),
		rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
		scale(glm::vec3(1.0f, 1.0f, 1.0f))
	{

	}

	void doLocal(glm::mat4 & transMatrix) {	
		//解开这两个设置，能得到Unity相同效果。
		//transMatrix = glm::rotate(transMatrix, glm::radians(-rotation.x), axis_x);
		//transMatrix = glm::rotate(transMatrix, glm::radians(-rotation.y), axis_y);
		transMatrix = glm::rotate(transMatrix, glm::radians(rotation.x), axis_x);
		transMatrix = glm::rotate(transMatrix, glm::radians(rotation.y), axis_y);
		transMatrix = glm::rotate(transMatrix, glm::radians(rotation.z), axis_z);
		transMatrix = glm::translate(transMatrix, position);
		transMatrix = glm::scale(transMatrix, scale);
	}
};

glm::vec3 Transform::axis_x = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 Transform::axis_y = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 Transform::axis_z = glm::vec3(0.0f, 0.0f, 1.0f);
glm::mat4 Transform::identity = glm::mat4(1.0f);