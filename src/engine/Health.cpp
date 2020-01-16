#include "Health.h"
#include "stb_image.h"
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 1020



void Health::RenderInitialise(char* _shader, std::shared_ptr<Collision> _col)
{
	col = _col;
	std::sr1::shared_ptr<Application> app = getApp();


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
	mesh = app->context->createMesh();

	std::sr1::shared_ptr<rend::Buffer> posBuffer = app->context->createBuffer();
	{
		posBuffer->add(glm::vec2(0, 0));
		posBuffer->add(glm::vec2(0, 1));
		posBuffer->add(glm::vec2(1, 1));
		posBuffer->add(glm::vec2(1, 1));
		posBuffer->add(glm::vec2(1, 0));
		posBuffer->add(glm::vec2(0, 0));
		mesh->setBuffer("a_Position", posBuffer);
	}

	std::sr1::shared_ptr<rend::Buffer> texBuffer = app->context->createBuffer();
	{
		texBuffer->add(glm::vec2(0, 1));
		texBuffer->add(glm::vec2(0, 0));
		texBuffer->add(glm::vec2(1, 0));
		texBuffer->add(glm::vec2(1, 0));
		texBuffer->add(glm::vec2(1, 1));
		texBuffer->add(glm::vec2(0, 1));
		mesh->setBuffer("a_TexCoord", texBuffer);
	}

}


void Health::rendTex(char * _tex)
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
	health.push_back(texture);
}
void Health::onGetHit(int healthHit)
{
	imgNum = healthHit;
}

void Health::getInputCont(int _num)
{
	numb = _num;
}

void Health::onDisplay()
{
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);
	glDisable(GL_DEPTH_TEST);
	//add transform
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(pos.x, pos.y, 0));
	model = glm::scale(model, glm::vec3(pos.z, pos.w, 1));
	shader->setUniform("u_Projection", glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f));
	shader->setUniform("u_Model", model);
	mesh->setTexture("u_Texture", health[imgNum]);
	shader->setMesh(mesh);
	if (gamePause == true)
	{
		gameKey = false;
		gamePause = false;

	}
	if (gameKey == true)
	{
		shader->render();
		gamePause = false;
	}

}
void Health::setPosition(glm::vec4 size)
{
	pos = size;
}

void Health::onTick()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE] || numb == 1)
	{
		gameKey = true;
	}
	if (state[SDL_SCANCODE_P] | numb == 2)
	{
		gamePause = true;
	}
}