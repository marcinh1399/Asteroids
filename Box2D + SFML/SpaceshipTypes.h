#pragma once
#include "Statistics.h"
#include <utility>
#include <SFML\Graphics.hpp>
#include <array>


enum class ShipType {
	type1 = 0,
	type2
	//.
	//.
	//.
};



class SpaceshipTypes
{

private:
	std::array<std::pair<sf::ConvexShape *, Statistics>, 1> types;

	void loadTypes();

	std::pair<sf::ConvexShape *, Statistics> setType0();

public:
	SpaceshipTypes();

	std::pair<sf::ConvexShape *, Statistics> getType(ShipType type);

	~SpaceshipTypes();
};

