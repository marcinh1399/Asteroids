#include "stdafx.h"
#include "SpaceshipTypes.h"


void SpaceshipTypes::loadTypes()
{
	ship_types[0] = setType0();
}

Ship * SpaceshipTypes::setType0()
{
	// SHAPE //

	size_t points = 4;

	sf::Vector2f * vertices = new sf::Vector2f[points]{
		sf::Vector2f(0.f, -20.f),
		sf::Vector2f(-15.f, 20.f),
		sf::Vector2f(0.f, 1.f),
		sf::Vector2f(15.f, 20.f)
	};

	sf::ConvexShape shape(points);

	for (int i = 0; i < points; ++i)
	{
		shape.setPoint(i, vertices[i]);
	}

	delete[] vertices;

	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::White);
	shape.setFillColor(sf::Color::Transparent);

	/// END SHAPE ///

	// STATS //

	float hp{ 300.f };
	float speed{ 30.f };
	float radians_per_second{ Coords::radians(120.f) };   ///{ 7.f };
	float armor{ 0.8f };
	float damage_of_bullets{ 0.9f };
	float bullet_cooldown{ 0.6f };
	float xyz = 100.f;

	Statistics stats{
		hp,
		speed,
		radians_per_second,
		armor,
		damage_of_bullets,
		bullet_cooldown
	};

	return new Ship(stats, shape);
}


SpaceshipTypes::SpaceshipTypes()
{
	loadTypes();
}

Ship * SpaceshipTypes::getType(ShipType type)
{
	return ship_types[static_cast<int>(type)];
}

SpaceshipTypes * SpaceshipTypes::getInstance()
{
	if (instance == nullptr)
	{
		instance = new SpaceshipTypes();
	}

	return instance;
}


SpaceshipTypes::~SpaceshipTypes()
{
	for (auto ship : ship_types)
	{
		delete ship;
	}
}
