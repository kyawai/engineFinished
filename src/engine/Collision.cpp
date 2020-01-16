#include "Collision.h"
#include <ctime>
#include <chrono>
#include <thread>
void Collision::onIni()
{
		std::shared_ptr<Entity> colEnt = getEntity();
		std::shared_ptr<Transform> tran = colEnt->getComponent<Transform>();
		size = glm::vec3(0.3,0.2,0.3);
		offset = glm::vec3(0.0,0.0,0.0);
		
}

void Collision::onTick()
{
		collisionBox(healthH);
}


int Collision::collisionBox(int &_isCol)
{
	if (_isCol == 0) {_isCol = 0;}
		std::sr1::shared_ptr<Application> app = getApp();
		std::sr1::shared_ptr<Entity> ent = getEntity();
		std::sr1::shared_ptr<Transform> tran = ent->getComponent<Transform>();
		glm::vec3 np = tran->getPos() + offset;
		std::vector<std::sr1::shared_ptr<Entity>> ents;
		ents = app->getEntities<Collision>();
		for (std::vector<std::sr1::shared_ptr<Entity>>::iterator it = ents.begin(); it != ents.end(); it++)
		{
				if ((*it) != getEntity())
				{
					bool isHittingNow = false;
						std::sr1::shared_ptr<Collision> bc = (*it)->getComponent<Collision>();
						glm::vec3 sp = bc->getCollision(np, size);
						hit = bc->isColliding(np, size);
						bc->hit = hit;
						if (hit)
						{
							if (_isCol < 5)
							{
								if (timer > 0) { timer--; }
								if (timer == 0)
								{
									if (_isCol == 0) { _isCol++; }
									else if (_isCol == 1) { _isCol++; }
									else if (_isCol == 2) { _isCol++; }
									else if (_isCol == 3) { _isCol++; }
									else if (_isCol == 4) { _isCol++; }
									else if (_isCol == 5) { _isCol++; }
									if (hel != NULL)
									{
										hel->onGetHit(_isCol);
									}
									timer = 12;
								}

							}
							if (_isCol >= 5)
							{
								pau->onGetHit(_isCol);
								std::cout << "you died " << std::endl;
							}

								
						}
						np = sp;
						np = np - offset;
						tran->SetPos(np);
						lastPos = np;
				}

		}
		return _isCol;
}

bool Collision::isColliding(glm::vec3 pos, glm::vec3 size)
{
	isHittingnow = false;
		std::sr1::shared_ptr<Entity> ent = getEntity();
		std::sr1::shared_ptr<Transform> tran = ent->getComponent<Transform>();
		glm::vec3 a = tran->getPos() + offset;
		glm::vec3 as = this->size;
		glm::vec3 b = pos;
		glm::vec3 bs = size;
		if (a.x > b.x) // a right of b
		{
				if (a.x - as.x > b.x + bs.x) // left edge of a greater than right edge of b (not colliding)
				{
					hit = false;
					return false;
				}
		}
		else
		{
				if (b.x - bs.x > a.x + as.x)
				{
					hit = false;
					return false;
						
				}
		}

		if (a.z > b.z) // a front of b
		{
				if (a.z - as.z > b.z + bs.z) // back edge of a greater than front edge of b (not colliding)
				{
					hit = false;
					return false;
				}
		}
		else
		{
				if (b.z - bs.z > a.z + as.z)
				{
					hit = false;
					return false;
				}
		}

		if (a.y > b.y) // a above b
		{
				if (a.y - as.y > b.y + bs.y) // bottom edge of a greater than top edge of b (not colliding)
				{
					hit = false;
					return false;
				}
		}
		else
		{
				if (b.y - bs.y > a.y + as.y)
				{
					hit = false;
					return false;
				}
		}
		hit = true;
		isHittingnow = true;
		return true;

}

bool Collision::isHit()
{

	if (hit)
	{
		std::cout << "thitoevkjt" << std::endl;
	}
	return hit;

}

glm::vec3 Collision::getCollision(glm::vec3 pos, glm::vec3 size)
{
		float amount = 0.01f;
		float step = 0.01f;
		while(true)
		{
				if (!isColliding(pos, size)) break;
				pos.x += amount;
				if (!isColliding(pos, size)) break;
				pos.x -= amount;
				pos.x -= amount;
				if (!isColliding(pos, size)) break;
				pos.x += amount;
				pos.z += amount;
				if (!isColliding(pos, size)) break;
				pos.z -= amount;
				pos.z -= amount;
				if (!isColliding(pos, size)) break;
				pos.z += amount;
				pos.y += amount;
				if (!isColliding(pos, size)) break;
				pos.y -= amount;
				pos.y -= amount;
				if (!isColliding(pos, size)) break;
				pos.y += amount;
				amount += step;
		}
		return pos;

}

void Collision::setOffset(const glm::vec3 offset)
{
		this->offset = offset;
}

void Collision::setSize(const glm::vec3 & size)
{
		this->size = size;
}

void Collision::setHealth(std::shared_ptr<Health> _hel)
{
	hel = _hel;
}
void Collision::setPau(std::shared_ptr<Pause> _pau)
{
	pau = _pau;
}
