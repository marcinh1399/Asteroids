#include "stdafx.h"
#include "ScreenManager.h"
#include "SFML\Graphics.hpp"






ScreenManager::ScreenManager(std::vector<std::unique_ptr<Object>> & v_objects,
	std::vector< std::unique_ptr<Animation> > & v_explosions,
	std::unique_ptr<sf::RenderWindow> & u_window)
	: objects{ v_objects }, expl_animations { v_explosions }, _window{ u_window } {}

void ScreenManager::display()
{
	_window->clear();

	for (auto & object : objects)
	{
		auto * shape = object->getShape();
		_window->draw(*shape);
	}
	
	for (auto & animation : expl_animations)
	{
		auto _frame = animation->getFrame(0.f); // it has been updated in animations()
		_window->draw(*_frame);
	}

	_window->display();
}

ScreenManager::~ScreenManager()
{
}
