#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <memory>
#include <vector>
#include <list>
#include "Environment.h"
#include "Transform.h"
#include "Entity.h"
#include "Component.h"
#include "Renderer.h"
#include <rend/rend.h>
#include "SDL2/SDL.h"
#include "Audio.h"
#include "Collision.h"
#include "Health.h"
#include "ModelController.h"
#include "Pause.h"
#include "Camera.h"

class Application;
class Entity;
class ModelController;
class Pause;
class Health;
class Camera;

class Application
{
	friend Entity;
	bool running;
	std::vector<std::shared_ptr<Entity>> entities;
	std::weak_ptr<Application> self;
	std::shared_ptr<ModelController> mod;
	std::shared_ptr<Pause> pause;
	std::shared_ptr<Health> hel;
	std::shared_ptr<Camera> cam;
	SDL_Window* window;
	ALCdevice* device;
	ALCcontext* soundContext;
	int entNum;

public:
	std::sr1::shared_ptr<rend::Context> context;
	static std::shared_ptr<Application> Initialize();
	void Run();
	std::shared_ptr<Entity> AddEntity();
	void setCon(std::shared_ptr<ModelController> _mod);
	void setPause(std::shared_ptr<Pause> _p);
	void setHel(std::shared_ptr<Health> _h);
	void setCam(std::shared_ptr<Camera> _c);
	void Stop();
	~Application();
	int num;
	float lastTime;
	float time;
	float diff;
	float deltaTime;
	float idealTime;

	template<class T>
	std::vector<std::shared_ptr<Entity>> getEntities()
	{
			bool ret;
			std::vector<std::shared_ptr<Entity>> retVec;
			for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin(); it != entities.end(); it++)
			{
					ret = (*it)->checkComponent<T>();
					if (ret)
					{
							retVec.push_back(*it);
					}

			}
			return retVec;
	}
};

#endif // !_APPLICATION_H_
