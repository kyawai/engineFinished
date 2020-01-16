#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "Component.h"
#include "Application.h"
#include <rend/rend.h>
#include <sr1/memory>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include "GUI.h"
#include "Pause.h"
#include "GUI.h"

class GUI;
class Camera;
class Pause : public Component
{
	glm::vec4 pos;
	std::sr1::shared_ptr<rend::Shader> shader;
	std::sr1::shared_ptr<rend::Mesh> mesh;
	std::sr1::shared_ptr < rend::Texture> texture;
	int currImg;
	int time = 0;
	std::vector<std::shared_ptr<rend::Texture>> imgs;
public:
	void rendTex(char* _tex);
	void RenderInitialise(char* _shader);
	void setPosition(glm::vec4 _size);
	void onTick();
	void onDisplay();
	bool change = false;
	bool gameKey = false;
	bool gameUnPause = true;
	void onGetHit(int _hitNum);
	int hitNum;
	int numb;
	void getInputCont(int _num);
};

#endif