#ifndef _ANIM_H_
#define _ANIM_H_
#include "Application.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include "glm/gtx/string_cast.hpp"
#include <GL/glew.h>
#include <sr1/memory>

class Camera;
class Anim : public Component
{
	float angle;
	glm::vec4 pos;
	std::sr1::shared_ptr<rend::Shader> shader;
	std::sr1::shared_ptr<rend::Mesh> mesh;
	std::sr1::shared_ptr < rend::Texture> texture;
	int currImg;
	int time = 0;
	std::sr1::shared_ptr<Camera> camera;
	std::vector<std::shared_ptr<rend::Texture>> imgs;
public:
	void rendTex(char* _tex);
	void RenderInitialise(char* _shader, std::shared_ptr<Camera> _camera);
	void renderMesh(char * _mesh);
	void setPosition(glm::vec4 _size);
	void onTick();
	void onDisplay();
	bool change = false;
};
#endif
