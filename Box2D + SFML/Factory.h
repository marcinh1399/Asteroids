#pragma once
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include <memory>
#include "Asteroid.h"
#include "AsteroidGenerator.h"
#include "Player.h"
#include "SpaceshipTypes.h"
#include "Spaceship.h"
#include "Bullet.h"
#include "BulletShapes.h"


class Factory
{

private:

	std::unique_ptr<b2World> & _world;
	std::unique_ptr<AsteroidGenerator> asteroid_generator;
	sf::Vector2f world_bounds;
	std::shared_ptr<Player> _player;
	SpaceshipTypes * spaceship_types;
	BulletShapes bullet_shapes;
	


	struct BodyDescription
	{
		b2Vec2 position;
		b2BodyType type;
		b2Shape * shape;
		float density;
		float friction;
		float restitution;
		b2Vec2 linear_velocity;
		float angular_velocity;
	};


	b2Body * makeBody(const BodyDescription & desc, bool group);


public:
	Factory(std::unique_ptr<b2World> & world, sf::Vector2f world_bnds);


	std::unique_ptr<Asteroid> makeAsteroid();


	std::shared_ptr<Player> makePlayer(std::unique_ptr<Spaceship> & ship, 
		std::shared_ptr<KeyboardHandling> keyboard);


	std::unique_ptr<Spaceship> makeSpaceship(sf::Vector2f sf_pos, 
		SpaceshipTypes::ShipType type, std::shared_ptr<KeyboardHandling> keyboard);


	std::unique_ptr<Bullet> makeBullet(Bullet::Type type);


	~Factory();
};

