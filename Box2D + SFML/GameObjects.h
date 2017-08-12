#pragma once
#include <vector>
#include <memory>
#include "Object.h"
#include "Factory.h"
#include <Box2D\Box2D.h>
#include "Player.h"

class GameObjects
{

public:
	
	sf::Vector2f world_size;

	std::vector< std::unique_ptr<Object> > objects;
	std::vector< std::unique_ptr<Animation> > expl_animations;
	std::shared_ptr<KeyboardHandling> keyboard;
	std::unique_ptr<b2World> world;
	std::unique_ptr<Factory> factory;
	std::shared_ptr<Player> player;


	GameObjects(sf::Vector2f world_bounds, SpaceshipTypes::ShipType s_t, std::shared_ptr<KeyboardHandling> kb);
	~GameObjects();
};

