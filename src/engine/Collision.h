#ifndef _COLLISION_H_
#define _COLLISION_H_
#include "Component.h"
#include "Transform.h"
#include "Application.h"
#include "Entity.h"
#include "Health.h"
#include "Pause.h"
#include "GUI.h"

class Health;
class Pause;
class GUI;
class Collision : public Component
{
		glm::vec3 size;
		glm::vec3 offset;
		glm::vec3 lastPos;
		glm::vec3 newSize;
		void onTick();
	    std::shared_ptr<Health> hel;
		std::shared_ptr<Pause> pau;
		glm::vec3 getCollision(glm::vec3 pos, glm::vec3 size);

public:

		void onIni();
		void setOffset(const glm::vec3 offset);
		void setSize(const glm::vec3 &size);
		void setHealth(std::shared_ptr<Health> _hel);
		void setPau(std::shared_ptr<Pause> _pau);
		bool hit = false;
		bool isHit();
		int collisionBox(int &_isCol);
		int healthH = 0;
		bool isColliding(glm::vec3 pos, glm::vec3 size);
		bool healthBo = false;
		bool isHittingnow = false;
		int healthInt = 6;
		int timer = 0;
		int temp = 7;

};


#endif