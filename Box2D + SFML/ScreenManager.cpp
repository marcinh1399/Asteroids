#include "stdafx.h"
#include "ScreenManager.h"
#include "SFML\Graphics.hpp"



ScreenManager::ScreenManager(std::shared_ptr<GameObjects> g_objects, std::unique_ptr<sf::RenderWindow> & wind)
	: objects(g_objects->objects),
	expl_animations(g_objects->expl_animations),
	window(wind)
{
	border.setPointCount(128);
	border.setRadius(World::radius);
	//border.setPosition(World::radius, World::radius);
	border.setOutlineThickness(5);
	border.setOutlineColor(sf::Color::Red);
	border.setFillColor(sf::Color::Green);
	border2.setPointCount(128);
	border2.setRadius(World::radius - 200.f);
	border2.setPosition(200.f, 200.f);
	//border.setPosition(World::radius, World::radius);
	border2.setOutlineThickness(5);
	border2.setOutlineColor(sf::Color::Red);
	border2.setFillColor(sf::Color::Black);
}

void ScreenManager::display()
{
	window->clear();

	window->draw(border);
	window->draw(border2);

	for (auto & object : objects)
	{
		auto * shape = object->getShape();
		window->draw(*shape);

		if (auto p = dynamic_cast<Enemy *>(object.get()))
		{
			//sf::View view(p->getPosition(), window->getView().getSize());
			auto v = window->getView();
			v.setCenter(p->getPosition());
			window->setView(v);
		}
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
