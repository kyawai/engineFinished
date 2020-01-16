#include "Camera.h"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 1020
Camera::Camera()
{
}
Camera::~Camera()
{
}

void Camera::CamIni(float _angle)
{

		angle = _angle;
		posi = glm::vec3(1.0f);
}

glm::mat4 Camera::getView()
{
	return view;
}

glm::vec3 Camera::GetPos()
{
		std::shared_ptr<Entity> ent = getEntity();
		std::shared_ptr<Transform> tran = ent->getComponent<Transform>();
		return tran->pos;
}



glm::mat4 Camera::getProjection()
{
		projection = glm::perspective(glm::radians(angle), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		return projection;
}


glm::mat4 Camera::GetModel()
{
		std::shared_ptr<Entity> ent = getEntity();
		std::shared_ptr<Transform> tran = ent->getComponent<Transform>();
		view = glm::inverse(model);
		model = tran->GetModel();
		return model;
}

void Camera::getInputCont(int _num)
{
	numb = _num;
}



void Camera::onTick()
{
		std::shared_ptr<Entity> ent = getEntity();
		std::shared_ptr<Transform> tran = ent->getComponent<Transform>();

		const Uint8 *state = SDL_GetKeyboardState(NULL);
	
		if (state[SDL_SCANCODE_A] || numb == 6 )
		{
				float temp = tran->GetRotation();
				float temp2 = temp;
				if (temp2 < 6)
				{
						tran->AddRotation(0.4, 0, 0);
				}
		}
		if (state[SDL_SCANCODE_D] || numb == 3)
		{
				float temp = tran->GetRotation();
				float temp2 = temp;
				if (temp2 > -6)
				{
						tran->AddRotation(-0.4, 0, 0);
				}
		}
		GetModel();
}