#include "stdafx.h"
#include "ScreenManager.h"
#include "SFML\Graphics.hpp"




ScreenManager::ScreenManager(std::vector<Object*>& v_objects, std::unique_ptr<sf::RenderWindow> & u_window)
	: objects(v_objects), _window(u_window) {}

void ScreenManager::display()
{
	_window->clear();

	for (auto _object : objects)
	{
		auto * shape = _object->getShape();
		_window->draw(*shape);
	}

	_window->display();
}

ScreenManager::~ScreenManager()
{
}
