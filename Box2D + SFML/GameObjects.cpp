#include "stdafx.h"
#include "GameObjects.h"



GameObjects::GameObjects(sf::Vector2f world_bounds, SpaceshipTypes::ShipType s_t, std::shared_ptr<KeyboardHandling> kb)
	: world_size(world_bounds),
	keyboard(kb)
{
	world = std::make_unique<b2World>(b2Vec2(0.f, 0.f));
	factory = std::make_unique<Factory>(world, world_bounds);
	auto spaceship = factory->makeSpaceship(sf::Vector2f(world_bounds.x / 2, world_bounds.y / 2), s_t);
	player = factory->makePlayer(spaceship, kb);
	objects.push_back(std::move(spaceship));
}

GameObjects::~GameObjects()
{
	
}
