#ifndef _HEALTH_H_
#define _HEALTH_H_
#include "Application.h"
#include "Component.h"
#include "Entity.h"
#include <algorithm>
#include <iterator>
#include <fstream>
#include <exception>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <sr1/memory>
#include "Camera.h"
#include <rend/rend.h>
#include "Collision.h"

class Collision;

class Health : public Component
{
	glm::vec4 pos;
	std::sr1::shared_ptr<rend::Shader> shader;
	std::sr1::shared_ptr<rend::Mesh> mesh;
	std::sr1::shared_ptr < rend::Texture> texture;
	std::vector <std::shared_ptr<rend::Texture>> health;
	std::shared_ptr<Collision> col;
	int healthInt;
public:
	int currHealth = 1;
	int healthHit = 0;
	void onDisplay();
	void setPosition(glm::vec4 size);
	void rendTex(char* _tex);
	void Health::RenderInitialise(char* _shader, std::shared_ptr<Collision> _col);
	bool changeTex = false;
	void onTick();
	int imgNum;
	void Health::onGetHit(int healthHit);
	bool gameKey = false;
	bool gamePause = false;
	int numb;
	void getInputCont(int _num);

};

#endif