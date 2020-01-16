#include <iostream>
#include "Application.h"
#include "PBR.h"
#include <algorithm>
#include <GL/GLU.h>
#include <SDL2/SDL_gamecontroller.h>
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 1020
const float aspect = float(WINDOW_WIDTH) / WINDOW_HEIGHT;

std::shared_ptr<Application> Application::Initialize()
{
	std::shared_ptr<Application> ini = std::make_shared<Application>();
	ini->self = ini;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw rend::Exception("Failed to initialise at Application::Initialize");
	}
	if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
	{
		throw rend::Exception("failed to initialise game controller");
	}

	ini->window = SDL_CreateWindow("MYENGINE",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(ini->window))
	{
		throw rend::Exception("failed to create window");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(ini->window);
	if (!glContext)
	{
		throw rend::Exception("failed to create opengl cotext");
	}

	ini->device = alcOpenDevice(NULL);

	if (!ini->device)
	{
			throw std::exception();
	}
	ini->soundContext = alcCreateContext(ini->device, NULL);

	if (!ini->soundContext)
	{
			alcCloseDevice(ini->device);
			throw std::exception();
	}
	if (!alcMakeContextCurrent(ini->soundContext))
	{
			alcDestroyContext(ini->soundContext);
			alcCloseDevice(ini->device);
			throw std::exception();
	}
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);

	ini->context = rend::Context::initialize();

	ini->lastTime = SDL_GetTicks();
	
	SDL_GameController *controller = nullptr;

	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (SDL_IsGameController(i))
		{
			controller = SDL_GameControllerOpen(i);
			break;
		}
	}

	return ini;


}

Application::~Application()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
	alcMakeContextCurrent(NULL);
	alcDestroyContext(soundContext);
	alcCloseDevice(device);
}


std::shared_ptr<Entity> Application::AddEntity()
{
	std::shared_ptr<Entity> ent = std::make_shared<Entity>();
	entities.push_back(ent);
	ent->app = self;
	ent->self = ent;


	return ent;
}

void Application::setCon(std::shared_ptr<ModelController> _mod)
{
	mod = _mod;
}

void Application::setPause(std::shared_ptr<Pause> _p)
{
	pause = _p;
}

void Application::setHel(std::shared_ptr<Health> _h)
{
	hel = _h;
}

void Application::setCam(std::shared_ptr<Camera> _c)
{
	cam = _c;
}

void Application::Run()
{

	bool quit = false;
	while (!quit)
	{
		time = SDL_GetTicks();
		diff = lastTime - time;
		deltaTime = diff / 1000;

		idealTime = 1.0f / 60.0f;
		if (idealTime > deltaTime)
		{
			SDL_Delay(idealTime - deltaTime);
		}

		glClearColor(0.10f, 0.15f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		SDL_Event event = { 0 };
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			else if(event.type == SDL_CONTROLLERBUTTONDOWN)
			{
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
				{
					num = 1;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
				{
					num = 2;
				}
				pause->getInputCont(num);
				hel->getInputCont(num);
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
				{
					num = 3;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
				{
					num = 4;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP)
				{
					num = 5;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
				{
					num = 6;
				}
				mod->getInputCont(num);
				cam->getInputCont(num);
			}
			if (event.type == SDL_CONTROLLERBUTTONUP)
			{
				num = 0;
				mod->getInputCont(num);
			}
		}
		for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin(); it != entities.end(); it++)
		{
			(*it)->tick();

			//	std::cout << "entity tick" << std::endl;
		}


		for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin(); it != entities.end(); it++)
		{
			(*it)->display();
			//	std::cout << "entities display" << std::endl;
		}

		SDL_GL_SwapWindow(window);
	}
}

void Application::Stop()
{
	running = false;
}
