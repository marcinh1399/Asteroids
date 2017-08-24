#pragma once
#include "Statistics.h"
#include <utility>
#include <SFML\Graphics.hpp>
#include <array>
#include "Ship.h"
#include "Coords.h"




class SpaceshipTypes
{

private:

	static SpaceshipTypes * instance;

	SpaceshipTypes();

	SpaceshipTypes(const SpaceshipTypes & type) = delete;

	SpaceshipTypes& operator=(const SpaceshipTypes & type) = delete;

	void loadTypes();

	Ship * setType0();


	std::array<Ship *, 1> ship_types;
	

	
public:

	enum class ShipType {
		type1 = 0,
		none
	};

	Ship * getType(ShipType type);

	static SpaceshipTypes * getInstance();

	~SpaceshipTypes();
};

