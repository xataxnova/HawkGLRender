#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class Matrix {
public:
	Matrix() {
		mat = glm::mat4(1.0f);
	}

	void doTranslate(float x, float y, float z) {
		mat = glm::translate(mat, glm::vec3(z,y,z));
	}

	void doTest() {
		glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
		vec = trans * vec;
		std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;
	}
private:
	glm::mat4 mat;
};

