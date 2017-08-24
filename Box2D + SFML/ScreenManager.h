#pragma once
#include "Object.h"
#include <vector>
#include <memory>
#include "GameObjects.h"
#include <SFML\Graphics.hpp>


class ScreenManager
{

private:

	std::vector<std::unique_ptr<Object>> & objects;
	std::vector< std::unique_ptr<Animation> > & expl_animations;
	std::unique_ptr<sf::RenderWindow> & window;

	sf::CircleShape border;
	sf::CircleShape border2;


public:

	ScreenManager(std::shared_ptr<GameObjects> g_objects, std::unique_ptr<sf::RenderWindow> & wind);

	void display();

	~ScreenManager();
};

