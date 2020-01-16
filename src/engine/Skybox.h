#ifndef  _SKYBOX_H_
#define _SKYBOX_H_
#include <gl/glew.h>
#include <string>
#include <stb_image.h>
#include <iostream>
#include "Application.h"
class Skybox : public Component
{
		//set camera
		std::shared_ptr<Camera> cam;
public:
		void SkyboxInitialize(std::shared_ptr<Camera> _cam);
		virtual void onTick();
};




#endif // ! _SKYBOX_DEFINE_
