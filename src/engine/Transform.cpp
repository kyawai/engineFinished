#include "Transform.h"

Transform::~Transform()
{
}

Transform::Transform()
{
		rotY = 0.0f;
		rotX = 0.0f;
		rotZ = 0.0f;
		pos = glm::vec3(0.0f, 0.0f, 0.0f);;
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0f);
}

glm::mat4 Transform::GetModel()
{
		model = glm::mat4(1.0f);
		model = glm::translate(model, pos);
		model = glm::rotate(model, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
	  model = glm::rotate(model, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, scale);
		return model;
}

glm::vec3 Transform::getPos()
{
		return pos;
}

void Transform::SetPos(glm::vec3 _pos)
{
		pos = _pos;
}

void Transform::AddPos(glm::vec3 _pos)
{
		pos += _pos;
}

float Transform::GetRotation()
{
		return rotY;
}

void Transform::SetRotation(float _rotY, float _rotX, float _rotZ)
{
		rotY = _rotY;
		rotX = _rotX;
		rotZ = _rotZ;
}

void Transform::AddRotation(float _rotY, float _rotX, float _rotZ)
{
		rotY += _rotY;
		rotX += _rotX;
		rotZ += _rotZ;
}

glm::vec3 Transform::getScale()
{
		return scale;
}

void Transform::SetScale(glm::vec3 _scale)
{
		scale = _scale;
}
