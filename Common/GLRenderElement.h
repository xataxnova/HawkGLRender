#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector> 
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Transform.h"
#include "Camera.h"
#include "GameElement.h"

class GLRenderElement : public GameElement {	
public:
	Transform transform;
protected:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	Shader *shader;
	Texture2D *texture;
public:		
	virtual void prepare() = 0;
	virtual void render( Camera *currentCam ) = 0;		
};