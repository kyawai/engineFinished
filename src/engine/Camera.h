#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Component.h"
#include "Application.h"
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include "glm/gtx/string_cast.hpp"
#include <cmath>
#include "Pause.h"


class Camera : public Component
{
		glm::vec3 posi;
		glm::mat4 view;
		glm::mat4 projection;
		float angle;
		glm::mat4 model;
		bool quit = false;
		glm::vec3 rotX;
public:
		Camera();
		~Camera();
		void CamIni(float _angle);
		glm::mat4 getView();
		glm::vec3 GetPos();
		glm::mat4 getProjection();
		void Camera::onTick();
		glm::mat4 GetModel();
		int numb;
		void getInputCont(int _num);
};

#endif

