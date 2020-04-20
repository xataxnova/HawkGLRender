#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector> 
#include <iostream>
#include "../Common/Common.h"

class GLTriangleWithColoredVertex : public GLRenderElement 
{
public:
	void prepare() {
		shader = new Shader("shaders/vertexColorTriangle.vs", "shaders/vertexColorTriangle.fs");
		shader->use();

		logMaxVertexPropertySupported();

		initBuffer();		
		fillBuffer();
		setupAttribute();
		//unbindBuffer();
	}
	void render( Camera *currentCam ) {
		shader->use();
		shader->setVec4f("shiftPos", 0.2f, 0.2f, 0, 0);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}
	~GLTriangleWithColoredVertex() {
		delete shader;
	}
private:
	void logMaxVertexPropertySupported() {
		int nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	}

	void initBuffer() {
		glGenVertexArrays(1, &VAO); 
		glBindVertexArray(VAO);
		
		glGenBuffers(1, &VBO);		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);		
	}

	void fillBuffer() {
		float vertices[] = {
			// λ��              // ��ɫ
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
		};		
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}

	void setupAttribute() {			
		/*
			Param 1: ���ı�����Ե�����,û��һ������+1
			Param 2: size
			Param 3: ��������
			Param 4: �Ƿ��׼��
			Param 5��Stride��������
			Param 6: û̫����offset��ƫ��������һ�����Խ���ʱ�����һ��λ��
		*/
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void unbindBuffer() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


};
