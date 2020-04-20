#pragma once
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

///目前的Texture2D类，是不考虑MipMap的以后可以扩展
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
		glBindTexture(GL_TEXTURE_2D, texture);//思考怎么绑定多张贴图呢？
	}

	//在指定位置上绑定贴图，参数为0-15，共16个贴图位
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

			//这里注意一下，GL_TEXTURE_2D是 指定的一个纹理目标，
			glBindTexture(GL_TEXTURE_2D, texture);

			//为当前绑定的纹理，设置环绕，过滤方式
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
				GL_TEXTURE_2D,  //纹理类型（目标）
				0,				//MipMap等级，0为基础级别
				internalFormat,			//纹理存储为何种格式
				width,
				height,
				0,				//历史遗留问题，填0即可
				sourceFormat,			//原图类型
				GL_UNSIGNED_BYTE,//原图存储类型。
				data
			);		
			glGenerateMipmap(GL_TEXTURE_2D);

			//如果需要生成MipMap，则在删除数据之前做这件事。
			//图片加载到GPU之后，就可以释放掉了没必要保持两份
			stbi_image_free(data);
		}
		else {
			std::cout << "Error pic not found!!!!"<< image_path;
		}
	}
};