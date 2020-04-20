#pragma once
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

///Ŀǰ��Texture2D�࣬�ǲ�����MipMap���Ժ������չ
class Texture2D {
public:
	int width;
	int height;
	int nrChannels;
	unsigned int texture;
	unsigned char *data;
	GLint wrapMode = GL_REPEAT;
	GLint filterMode = GL_LINEAR;
	GLint internalFormat = GL_RGB;
	GLint sourceFormat = GL_RGB;
	float borderColor[4];
public:
	Texture2D() {

	}

	auto selectTextureFormatRGB() {
		internalFormat = GL_RGB;
		return this;
	}

	auto selectSourceFormatRGB() {
		sourceFormat = GL_RGB;
		return this;
	}

	auto selectRepeat() {
		wrapMode = GL_REPEAT;
		return this;
	}

	auto selectMirrorRepeat() {
		wrapMode = GL_MIRRORED_REPEAT;
		return this;
	}

	auto selectClampToEdge() {
		wrapMode = GL_CLAMP_TO_EDGE;
		return this;
	}

	auto selectClampToBorder(float r, float g, float b, float a) {
		borderColor[0] = r;
		borderColor[1] = g;
		borderColor[2] = b;
		borderColor[3] = a;
		wrapMode = GL_CLAMP_TO_EDGE;
		return this;
	}

	auto selectLinearFilter() {
		filterMode = GL_LINEAR;
		return this;
	}

	auto selectNearestFilter(){
		filterMode = GL_NEAREST;
		return this;
	}

	void use() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);//˼����ô�󶨶�����ͼ�أ�
	}

	//��ָ��λ���ϰ���ͼ������Ϊ0-15����16����ͼλ
	void use(int textureIndex) {
		if (textureIndex >= 0 && textureIndex < 16) {
			glActiveTexture(GL_TEXTURE0 + textureIndex);
			glBindTexture(GL_TEXTURE_2D, texture);
		}
	}
		
	void generateTexture(std::string image_path) {
		stbi_set_flip_vertically_on_load(true);
		data = stbi_load(image_path.c_str(), &width, &height, &nrChannels, 0);

		if ( data != NULL ) 
		{
			glGenTextures(1, &texture);

			//����ע��һ�£�GL_TEXTURE_2D�� ָ����һ������Ŀ�꣬
			glBindTexture(GL_TEXTURE_2D, texture);

			//Ϊ��ǰ�󶨵��������û��ƣ����˷�ʽ
			if (wrapMode != GL_CLAMP_TO_BORDER) {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
			}
			else {
				glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
						
			glTexImage2D(
				GL_TEXTURE_2D,  //�������ͣ�Ŀ�꣩
				0,				//MipMap�ȼ���0Ϊ��������
				internalFormat,			//����洢Ϊ���ָ�ʽ
				width,
				height,
				0,				//��ʷ�������⣬��0����
				sourceFormat,			//ԭͼ����
				GL_UNSIGNED_BYTE,//ԭͼ�洢���͡�
				data
			);		
			glGenerateMipmap(GL_TEXTURE_2D);

			//�����Ҫ����MipMap������ɾ������֮ǰ������¡�
			//ͼƬ���ص�GPU֮�󣬾Ϳ����ͷŵ���û��Ҫ��������
			stbi_image_free(data);
		}
		else {
			std::cout << "Error pic not found!!!!"<< image_path;
		}
	}
};