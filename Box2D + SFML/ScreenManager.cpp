#include "stdafx.h"
#include "ScreenManager.h"
#include "SFML\Graphics.hpp"



ScreenManager::ScreenManager(std::shared_ptr<GameObjects> g_objects, std::unique_ptr<sf::RenderWindow> & wind)
	: objects(g_objects->objects),
	expl_animations(g_objects->expl_animations),
	window(wind)
{
}

void ScreenManager::display()
{
	window->clear();

	for (auto & object : objects)
	{
		auto * shape = object->getShape();
		window->draw(*shape);
	}
	
	for (auto & animation : expl_animations)
	{
		auto _frame = animation->getFrame(0.f); // it has been updated in animations()
		window->draw(*_frame);
	}

	window->display();
}

ScreenManager::~ScreenManager()
{
}
