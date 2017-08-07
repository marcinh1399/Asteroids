#pragma once
#include <memory>
#include "Player.h"
#include "Spaceship.h"
#include "SpaceshipTypes.h"
#include "Statistics.h"
#include <Box2D\Box2D.h>
#include "Coords.h"

class PlayerBuilder
{

private:
	SpaceshipTypes types;
	std::unique_ptr<b2World> & _world;
	sf::Vector2f position;

	const float density{ 5.f };
	const float friction{ 0.6f };
	const float hp_multipier{ 10.f };

	b2Body * makeBody(sf::Shape * _shape);

public:
	PlayerBuilder(std::unique_ptr<b2World> & world, sf::Vector2f pos);

	std::unique_ptr<Player> makePlayer(ShipType type, std::shared_ptr<KeyboardHandling> keyboard);

	~PlayerBuilder();
};

