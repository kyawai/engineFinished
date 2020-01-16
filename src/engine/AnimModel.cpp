#include "AnimModel.h"
#include <stb_image.h>
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 1020


void AnimModel::rendTex(char * _tex)
{
	std::sr1::shared_ptr<Application> app = getApp();
	texture = app->context->createTexture();
	{
		int w = 0;
		int h = 0;
		int bpp = 0;

		unsigned char* data = stbi_load(_tex, &w, &h, &bpp, 3);
		if (!data)
		{
			throw rend::Exception("cant load texture");
		}
		texture->setSize(w, h);

		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				int size = y * w * 3 + x * 3;

				texture->setPixel(x, y, glm::vec3(data[size] / 255.0f, data[size + 1] / 255.0f, data[size + 2] / 255.0f));

			}
		}
		stbi_image_free(data);
	}
	texs.push_back(texture);
}

void AnimModel::RenderInitialise(char * _shader, std::shared_ptr<Camera> _camera)
{
	std::sr1::shared_ptr<Application> app = getApp();
	camera = _camera;
	mesh = app->context->createMesh();
	shader = app->context->createShader();
	{
		std::ifstream f(_shader);
		if (!f.is_open())
		{
			throw rend::Exception("cant open shader txt");
		}

		std::string shaderTxt;
		std::string pos;
		while (!f.eof())
		{
			std::getline(f, pos);
			shaderTxt += pos + "\n";
		}
		shader->parse(shaderTxt);
	}

}

void AnimModel::renderMesh(char * _model)
{
	std::sr1::shared_ptr<Application> app = getApp();
	mesh = app->context->createMesh();
	{
		std::ifstream f(_model);
		if (!f.is_open())
		{
			throw rend::Exception("cant open model txt");
		}

		std::string modelTxt;
		std::string pos;
		while (!f.eof())
		{
			std::getline(f, pos);
			modelTxt += pos + "\n";
		}
		mesh->parse(modelTxt);
	}
	models.push_back(mesh);
}

void AnimModel::setPosition(glm::vec4 _size)
{
	pos = _size;
}


void AnimModel::onDisplay()
{
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	glEnable(GL_DEPTH_TEST);

	std::sr1::shared_ptr<Entity> ent = getEntity();
	std::sr1::shared_ptr<Transform> transform = ent->getComponent<Transform>();
	shader->setUniform("u_Projection", camera->getProjection());
	shader->setUniform("u_View", camera->getView());
	shader->setUniform("u_Model", transform->GetModel());

	shader->setMesh(mesh);
	shader->render();
}
void AnimModel::onTick()
{
	std::sr1::shared_ptr<Application> app = getApp();
	if (time > 0) { time--; }
	if (time == 0)
	{
		if (change) { currImg--; }
		else { currImg++; }
		if (currImg >= models.size()) { change = true; currImg; }
		if (currImg <= 0) { change = false; }
		if (currImg == 8) { currImg = 1; }
		time = 10;
	}
	mesh = models[currImg];
	shader->setMesh(mesh);
	mesh->setTexture("u_Texture", texs[0]);
}