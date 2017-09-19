#pragma once
#include "Object.h"
#include <vector>
#include <memory>
#include "GameObjects.h"
#include <SFML\Graphics.hpp>
#include "EnemyAI.h"
#include "PlayerObject.h"
#include "World.h"


class ScreenManager
{

private:

	std::unique_ptr<sf::RenderWindow> & window;

	sf::CircleShape border;
	sf::CircleShape border2;


	GameObjects & game_objects;


public:

	ScreenManager(GameObjects & objects, std::unique_ptr<sf::RenderWindow> & wind);

	void display();

	~ScreenManager();
};

