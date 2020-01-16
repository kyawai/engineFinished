#ifndef  _GUI_H_
#define _GUI_H_

#include "Component.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <sr1/memory>
#include "Camera.h"
#include <rend/rend.h>

class Camera;
class GUI : public Component
{
		GLuint programId;
		GLuint vaoId;
		glm::vec4 pos;
		std::sr1::shared_ptr<rend::Shader> shader;
		std::sr1::shared_ptr<rend::Mesh> mesh;
		std::sr1::shared_ptr < rend::Texture> texture;
		float angle = 0;
public:
		std::vector<std::shared_ptr<GUI>> health;
		GUI();
		~GUI();
		void onDisplay();
		void RenderInitialise(char* _shader, char* _texture);
		void setPosition(glm::vec4 size);
};

#endif // ! _GUI_H_
