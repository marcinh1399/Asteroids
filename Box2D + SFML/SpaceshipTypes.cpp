#include "stdafx.h"
#include "SpaceshipTypes.h"


void SpaceshipTypes::loadTypes()
{
	types[0] = setType0();
}

std::pair<sf::ConvexShape*, Statistics> SpaceshipTypes::setType0()
{
	// SHAPE //

	size_t points = 4;

	sf::Vector2f * vertices = new sf::Vector2f[points]{
		sf::Vector2f{ 0.f, -20.f },
		sf::Vector2f{ -15.f, 20.f },
		sf::Vector2f{ 0.f, 1.f },
		sf::Vector2f{ 15.f, 20.f },
	};

	sf::ConvexShape * _shape = new sf::ConvexShape(points);

	for (int i = 0; i < points; ++i)
	{
		_shape->setPoint(i, vertices[i]);
	}

	delete[] vertices;

	_shape->setOutlineThickness(2);
	_shape->setOutlineColor(sf::Color::White);
	_shape->setFillColor(sf::Color::Transparent);

	/// END SHAPE ///

	// STATS //

	float hp{ 300.f };
	float speed{ 100.f };
	float radians_per_second{ 10.f };
	float armor{ 0.8f };
	float damage_of_bullets{ 0.9f };
	float bullet_cooldown{ 0.6f };

	Statistics stats{
		hp,
		speed,
		radians_per_second,
		armor,
		damage_of_bullets,
		bullet_cooldown
	};

	return std::pair<sf::ConvexShape*, Statistics>(_shape, stats);
}


SpaceshipTypes::SpaceshipTypes()
{
	loadTypes();
}

std::pair<sf::ConvexShape*, Statistics> SpaceshipTypes::getType(ShipType type)
{
	return types[static_cast<int>(type)];
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
	for (auto pair : types)
	{
		//delete pair.first;
	}
}
