#include "Skybox.h"


void Skybox::SkyboxInitialize(std::shared_ptr<Camera> _cam)
{
		cam = _cam;
}

void Skybox::onTick()
{
		//get transform component
		std::shared_ptr<Entity> ent = getEntity();
		std::shared_ptr<Transform> tran = ent->getComponent<Transform>();
		//get camera pos
		glm::vec3 camera = cam->GetPos();
		//set the position of the skybox to where the camera is
		tran->SetPos(camera);
		

}
