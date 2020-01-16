#ifndef _MODEL_CONTROLLER_H
#define _MODEL_CONTROLLER_H


#include "Component.h"
#include "Application.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include "glm/gtx/string_cast.hpp"



class ModelController : public Component
{
		glm::vec3 posi;
		glm::mat4 view;
		glm::mat4 projection;
		float angle;
		glm::mat4 model;
		bool quit = false;
		int timer = 0;
public:
		void modelIni();
		glm::mat4 getViewModel();
		glm::vec3 modelPos();
		glm::mat4 getModelProjection();
		void onTick();
		glm::mat4 getModel();
		int numb;
		void getInputCont(int _num);
};
#endif // ! _MODEL_CONTROLLER_H
