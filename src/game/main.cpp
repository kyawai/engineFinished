#include <iostream>
#include <memory>


#include <engine/Application.h>
#include <engine/Component.h>
#include <engine/Entity.h>
//#include <engine/Exception.h>
#include <engine/Renderer.h>
#include <engine/Transform.h>
#include <engine/PBR.h>
#include <engine/Skybox.h>
#include <engine/ModelController.h>
#include <engine/Collision.h>
#include <engine/GUI.h>
#include <engine/Pause.h>
#include <engine/AnimModel.h>

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 1020

int main()
{
		std::shared_ptr<Application> app = Application::Initialize();


		std::shared_ptr<Entity> cameraEnt = app->AddEntity();
		cameraEnt->setTag("CAMERA");
		std::shared_ptr<Transform> cameraTransform = cameraEnt->addComponent<Transform>();
		cameraTransform->SetPos(glm::vec3(0, 0, 10));
		cameraTransform->SetRotation(1, 1, 1);
		std::shared_ptr<Camera> camera = cameraEnt->addComponent<Camera>();

		camera->CamIni(65);
		app->setCam(camera);

		//add GUI

		std::shared_ptr<Entity> buttonEnt = app->AddEntity();
		buttonEnt->setTag("GUI1");
		std::shared_ptr<Transform> buttonTran = buttonEnt->addComponent<Transform>();
		std::shared_ptr<GUI> buttonRend = buttonEnt->addComponent<GUI>();
		buttonRend->setPosition(glm::vec4((700), (800), 400, 200));
		buttonRend->RenderInitialise("../shaders/GUI.txt", "../models/controlls.png");

		std::shared_ptr<Entity> conEnt = app->AddEntity();
		conEnt->setTag("GUI2");
		std::shared_ptr<Transform> conTran = conEnt->addComponent<Transform>();
		std::shared_ptr<GUI> conRend = conEnt->addComponent<GUI>();
		conRend->setPosition(glm::vec4((0), (800), 400, 200));
		conRend->RenderInitialise("../shaders/GUI.txt", "../models/cont.png");

		std::shared_ptr<Entity> pauseEnt = app->AddEntity();
		pauseEnt->setTag("PAUSE");
		std::shared_ptr<Pause> pauseRend = pauseEnt->addComponent<Pause>();
		pauseRend->RenderInitialise("../shaders/GUI.txt");
		pauseRend->rendTex("../models/anim/anim1.png");
		pauseRend->rendTex("../models/anim/anim2.png");
		pauseRend->rendTex("../models/anim/anim3.png");
		pauseRend->rendTex("../models/anim/anim4.png");
		pauseRend->rendTex("../models/anim/anim5.png");
		pauseRend->rendTex("../models/anim/anim6.png");
		pauseRend->rendTex("../models/anim/anim7.png");
		pauseRend->rendTex("../models/anim/anim8.png");
		pauseRend->rendTex("../models/anim/anim9.png");
		pauseRend->rendTex("../models/anim/anim10.png");
		pauseRend->rendTex("../models/anim/anim11.png");
		pauseRend->rendTex("../models/anim/anim12.png");
		pauseRend->rendTex("../models/anim/anim13.png");
		pauseRend->rendTex("../models/anim/anim14.png");
		pauseRend->setPosition(glm::vec4((WINDOW_WIDTH / 100 - 10), (WINDOW_HEIGHT / 100 - 10), 1080, 1020));
		app->setPause(pauseRend);
		//GUI // healthbar
		std::shared_ptr<Entity> guiEnt = app->AddEntity();
		guiEnt->setTag("GUI");
		//rend the background of health
		std::shared_ptr<Health> guiRend = guiEnt->addComponent<Health>();
	
		guiRend->rendTex("../models/fuelfull.png");
		guiRend->rendTex("../models/fuelmore.png");
		guiRend->rendTex("../models/fuelmed.png");
		guiRend->rendTex("../models/fuellower.png");
		guiRend->rendTex("../models/fuellow.png");
		guiRend->rendTex("../models/fuelBack.png");

		guiRend->setPosition(glm::vec4((WINDOW_WIDTH / 25), (WINDOW_HEIGHT / 25), 400, 100));

		app->setHel(guiRend);
		//character 
		std::shared_ptr<Entity> charEnt = app->AddEntity();
		charEnt->setTag("CHAR");
		std::shared_ptr<Transform> charTran = charEnt->addComponent<Transform>();
		std::shared_ptr<ModelController> charCont = charEnt->addComponent<ModelController>();
		std::shared_ptr<Collision> charCol = charEnt->addComponent<Collision>();
		charCol->onIni();
		charTran->SetRotation(100, 0, 0);
		charTran->SetPos(glm::vec3(0, 0, 5));
		charTran->SetScale(glm::vec3(0.025f));
		charCont->modelIni();
		charCol->setHealth(guiRend);
		charCol->setPau(pauseRend);
		app->setCon(charCont);

		guiRend->RenderInitialise("../shaders/GUI.txt", charCol);

		std::shared_ptr<AnimModel> charRend = charEnt->addComponent<AnimModel>();
		charRend->RenderInitialise("../shaders/basicShader.txt", camera);
		charRend->renderMesh("../models/char/mod1.obj");
		charRend->renderMesh("../models/char/mod2.obj");
		charRend->renderMesh("../models/char/mod3.obj");
		charRend->renderMesh("../models/char/mod4.obj");
		charRend->renderMesh("../models/char/5.obj");
		charRend->renderMesh("../models/char/mod4.obj");
		charRend->renderMesh("../models/char/mod3.obj");
		charRend->renderMesh("../models/char/mod2.obj");
		charRend->rendTex("../models/charTex.png");

		//add skybox
		std::shared_ptr<Entity> ent = app->AddEntity();
		std::shared_ptr<Transform> transform = ent->addComponent<Transform>();
		std::shared_ptr<Skybox> skybox = ent->addComponent<Skybox>();
		skybox->SkyboxInitialize(camera);
		transform->SetRotation(0,0,0);
		std::shared_ptr<Renderer> rend = ent->addComponent<Renderer>();
		rend->RenderInitialise("../shaders/basicShader.txt", "../models/Skybox.obj", "../models/space.png", camera);



		//add model rock
		std::shared_ptr<Entity> rockEnt = app->AddEntity();
		rockEnt->setTag("ROCK");
		std::shared_ptr<Transform> rockTran = rockEnt->addComponent<Transform>();
		std::shared_ptr<Collision> rockCol = rockEnt->addComponent<Collision>();
		rockTran->SetScale(glm::vec3(0.01f));
		rockCol->onIni();
		rockTran->SetPos(glm::vec3(-2, 0, 5));
		rockCol->setOffset({ 0, -0.5, 0 });
		rockCol->setSize({ 0.3, 0.3, 0.3 });
//	glm::vec3 chara = modelTran->getPos();

	std::shared_ptr<Renderer> rockRend = rockEnt->addComponent<Renderer>();
	rockRend->RenderInitialise("../shaders/basicShader.txt", "../models/rock.obj", "../models/rock.png", camera);
	

	//sound


	std::shared_ptr<Audio> sound = ent->addComponent<Audio>();
	sound->AudioInit("../sounds/OutThere.ogg");
	sound->PlayAudio();

	app->Run();

return 0;
}