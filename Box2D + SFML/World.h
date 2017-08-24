#pragma once
#include <SFML\Graphics.hpp>
#include <cstdlib>
#include "Coords.h"
#include <cmath>


class World
{

public:

	constexpr static int radius = 3000;
	constexpr static int safe_distance = 800;
	


	static sf::Vector2f asteroidStartingPosition();

	static sf::Vector2f asteroidDestPosition();

	static bool outOfMap(sf::Vector2f v);

	static bool inMap(sf::Vector2f v);

};

