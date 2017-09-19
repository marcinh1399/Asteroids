#include "stdafx.h"
#include "ScreenManager.h"
#include "SFML\Graphics.hpp"




ScreenManager::ScreenManager(GameObjects & objects, std::unique_ptr<sf::RenderWindow>& wind)
	: game_objects(objects),
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


	for (auto & pair : game_objects.objects)
	{
		auto * object = pair.second;

		auto * shape = object->getShape();
		window->draw(*shape);

		
		if (auto p = dynamic_cast<EnemyAI *>(object))
		{
			//sf::View view(p->getSFposition(), window->getView().getSize());
			auto v = window->getView();
			v.setCenter(p->getSFposition());
			window->setView(v);
		}
	
	}
	
	for (auto & animation : game_objects.explosions)
	{
		auto * _frame = animation.getFrame(0.f); // it has been updated in animations()
		//window->draw(*_frame);
	}

	window->display();
}

ScreenManager::~ScreenManager()
{
}
