#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>

#include "Renderer.h"
#include "Entity.h"

#include <exception>

#include <fstream>
#include "stb_image.h"


Renderer::Renderer()
{

}


void Renderer::onDisplay()
{
	std::sr1::shared_ptr<Entity> ent = getEntity();
	std::sr1::shared_ptr<Transform> transform = ent->getComponent<Transform>();
	shader->setUniform("u_Projection", camera->getProjection());
	shader->setUniform("u_View", camera->getView());
	shader->setUniform("u_Model", transform->GetModel());

	shader->setMesh(mesh);
	shader->render();
}

void Renderer::RenderInitialise(char* _shader, char* _model, char* _texture, std::shared_ptr<Camera> _camera)
{
	std::sr1::shared_ptr<Application> app = getApp();
	shader = app->context->createShader();
	camera = _camera;
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
	texture = app->context->createTexture();
	{
		int w = 0;
		int h = 0;
		int bpp = 0;

		unsigned char* data = stbi_load(_texture, &w, &h, &bpp, 3);
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
		mesh->setTexture("u_Texture", texture);
	}

}


Renderer::~Renderer()
{
	
}
