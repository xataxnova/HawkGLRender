#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector> 
#include <iostream>
#include "../Common/Common.h"

class GLRectWithTexture : public GLRenderElement {
public:
	float mixParam = 0.5f;
	Texture2D *second_texture;
public:
	void prepare() {
		float vertices[] = {
			//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
				 0.5f,  0.7f, 0.0f,   1.0f, 0.0f, 0.0f,   0.8f, 0.8f,   // ����
				 0.5f, -0.7f, 0.0f,   0.0f, 1.0f, 0.0f,   0.8f, 0.2f,   // ����
				-0.5f, -0.7f, 0.0f,   0.0f, 0.0f, 1.0f,   0.2f, 0.2f,   // ����
				-0.5f,  0.7f, 0.0f,   1.0f, 1.0f, 0.0f,   0.2f, 0.8f    // ����
		};

		unsigned int indices[] = { // ע��������0��ʼ! 
			0, 1, 3, // ��һ��������
			1, 2, 3  // �ڶ���������
		};

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//ע�� 8* sizeof(float)��stride�Ĵ�С��������������˶��ٸ�float������ͺ����һ��������;��ͻ��
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		texture = new Texture2D();
		texture->
			selectTextureFormatRGB()->selectSourceFormatRGB()->
			selectClampToEdge()->selectNearestFilter()->generateTexture("Resources/leg.jpg");

		second_texture = new Texture2D();
		second_texture->selectTextureFormatRGB()->selectSourceFormatRGB()
			->selectMirrorRepeat()->selectLinearFilter()->generateTexture("Resources/princess.jpg");

		shader = new Shader("shaders/textureRect.vs", "shaders/textureRect.fs");
	}

	void render( Camera *currentCam ) {
		shader->use();
		shader->setInt("texture1", 0);
		shader->setInt("texture2", 1);//������ͼ��ʱ���������Ҫ��ʾ����һ���ˡ�
		shader->setFloat("mixParam", mixParam);

		//Ӧ��MVP���󣬵�Shader
		currentCam->applyMVP(shader, transform );
		
		second_texture->use(0);
		texture->use(1);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	~GLRectWithTexture() {
		delete shader;
		delete texture;
		delete second_texture;
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void extraInputProcess( GLFWwindow *window) {
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {			
			mixParam += 0.05f;
			if (mixParam > 1.2f) mixParam = 1.2f;
		}

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			mixParam -= 0.05f;
			if (mixParam < -0.2f) mixParam = -0.2f;
		}
	}
};