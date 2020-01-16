#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Component.h"
#include <glm/gtx/transform.hpp>

class Transform : public Component
{

		glm::vec3 scale;

		float rotY;
		float rotX;
		float rotZ;


public:
		glm::mat4 model;
		~Transform();
		Transform();
		glm::mat4 GetModel();
		glm::vec3 pos;
	  glm::vec3 getPos();
		void SetPos(glm::vec3 _pos);
		void AddPos(glm::vec3 _pos);

		float GetRotation();
		void SetRotation(float _rotY, float _rotX, float _rotZ);
		void AddRotation(float _rotY, float _rotX, float _rotZ);

		glm::vec3 getScale();
		void SetScale(glm::vec3 _scale);


};


#endif // ! _TRANSFORM_H_

