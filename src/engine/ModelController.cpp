#include "ModelController.h"
#include <string>
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 1020

void ModelController::modelIni()
{
		posi = glm::vec3(1.0f);
		numb = 0;
}

glm::mat4 ModelController::getViewModel()
{
		return view;
}

glm::vec3 ModelController::modelPos()
{
		std::shared_ptr<Entity> ent = getEntity();
		std::shared_ptr<Transform> tran = ent->getComponent<Transform>();
		return tran->pos;
}

glm::mat4 ModelController::getModelProjection()
{
		projection = glm::perspective(glm::radians(angle), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		return projection;
}

void ModelController::onTick()
{

		std::shared_ptr<Entity> modEnt = getEntity();
		std::shared_ptr<Transform> modTran = modEnt->getComponent<Transform>();
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_A] || numb == 6)
		{
				glm::vec3 temp = modTran->pos;
				float temp2 = temp.x;
				if (temp2 > -4)
				{
						modTran->AddPos(glm::vec3(-0.1, 0, 0));
				}
		}
		if (state[SDL_SCANCODE_D] || numb == 3)
		{
				glm::vec3 temp = modTran->pos;
				float temp2 = temp.x;
				if (temp2< 4)
				{
						modTran->AddPos(glm::vec3(0.1, 0, 0));
				}
		}

		if (state[SDL_SCANCODE_W] || numb ==  5)
		{
				glm::vec3 temp = modTran->pos;
				float temp2 = temp.y;
				if (temp2 < 2.5f)
				{
						modTran->AddPos(glm::vec3(0, 0.1, 0));
				}
		}
		if (state[SDL_SCANCODE_S] || numb == 4)
		{
				glm::vec3 temp = modTran->pos;
				float temp2 = temp.y;
				if (temp2 > -3)
				{
						modTran->AddPos(glm::vec3(0, -0.1, 0));
				}
		}

		getModel();
}

glm::mat4 ModelController::getModel()
{
		std::shared_ptr<Entity> ent = getEntity();
		std::shared_ptr<Transform> tran = ent->getComponent<Transform>();
		model = tran->GetModel();
		view = glm::inverse(model);
		return model;
}

void ModelController::getInputCont(int _num)
{
	numb = _num;
}

