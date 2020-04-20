#pragma once
#include <vector>
#include "../Common/Common.h"

using namespace std;

//����ôд�ѣ�������������û����Object����Ҳû�������Ժ���˵�������Ȱ�OpenGL��������
class RenderManager {
private:
	vector<GLRenderElement*> renderQueue;
public:
	void ClearScreen() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	//������е�ʱ���Զ�Prapareһ�Ρ�
	void addRenderElement(GLRenderElement * newElement) {
		renderQueue.push_back(newElement);
		newElement->prepare();
	}

	void prepareAll() {
		for (size_t i = 0; i < renderQueue.size(); i++)
		{
			renderQueue[i]->prepare();
		}
	}

	void renderToCamera(Camera* cam) {
		ClearScreen();

		for (size_t i = 0; i < renderQueue.size(); i++)
		{						
			renderQueue[i]->render(cam);
		}
	}

	void dispose() {
		for (size_t i = 0; i < renderQueue.size(); i++)
		{
			delete renderQueue[i];
		}
		renderQueue.clear();
	}
};