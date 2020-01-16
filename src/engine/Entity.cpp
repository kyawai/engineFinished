#include "Entity.h"
#include <iostream>

std::shared_ptr<Application> Entity::getApplication(std::shared_ptr<Application> _app)
{
		return app.lock();
}

void Entity::tick()
{
	for (std::vector<std::shared_ptr<Component>>::iterator it = components.begin(); it != components.end(); it++)
	{
		(*it)->onTick();
//		std::cout << "entity on tick" << std::endl;
	}
}

void Entity::display()
{
	for (std::vector<std::shared_ptr<Component>>::iterator it = components.begin(); it != components.end(); it++)
	{
		(*it)->onDisplay();
	}
}

void Entity::setTag(char * Tag)
{
		tag = Tag;
}
