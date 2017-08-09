#pragma once
#include "Statistics.h"
#include <utility>
#include <SFML\Graphics.hpp>
#include <array>




class SpaceshipTypes
{

private:

	static SpaceshipTypes * instance;

	SpaceshipTypes();

	SpaceshipTypes(const SpaceshipTypes & type);

	std::array<std::pair<sf::ConvexShape *, Statistics>, 1> types;

	void loadTypes();

	std::pair<sf::ConvexShape *, Statistics> setType0();

	
public:

	enum class ShipType {
		type1 = 0,
		type2
		//.
		//.
		//.
	};

	std::pair<sf::ConvexShape *, Statistics> getType(ShipType type);

	static SpaceshipTypes * getInstance();

	~SpaceshipTypes();
};

