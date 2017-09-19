#pragma once
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include <memory>
#include "Asteroid.h"
#include "AsteroidGenerator.h"
#include "Player.h"
#include "SpaceshipTypes.h"
#include "Bullet.h"
#include "BulletShapes.h"
#include <boost\ptr_container\ptr_map.hpp>
#include "EnemyAI.h"
#include "PlayerObject.h"
#include "GameObjects.h"
#include "WeaponManager.h"


class Enemy;
class GameObjects;
class AI;





class Factory
{

private:

	using Keyboard = std::shared_ptr<KeyboardHandling>;


	AsteroidGenerator asteroid_generator;
	std::shared_ptr<Player> _player;
	SpaceshipTypes * spaceship_types;
	BulletShapes bullet_shapes;


	b2World & b2world;
	GameObjects & objects;
	


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

	Factory(b2World & world, GameObjects & game_objects);


	//Factory(std::shared_ptr<b2World> world, ObjectsMap map);


	Asteroid * makeAsteroid();


	/*
	std::shared_ptr<Player> makePlayer(std::unique_ptr<Spaceship> & ship, 
		std::shared_ptr<KeyboardHandling> keyboard);


	Spaceship * makeSpaceship(sf::Vector2f sf_pos, 
		SpaceshipTypes::ShipType type, Keyboard keyboard);
		*/

	PlayerObject * makePlayer(sf::Vector2f sf_pos, Keyboard keyboard, SpaceshipTypes::ShipType type);


	EnemyAI * makeEnemy();


	Bullet * makeBullet(Bullet::Type type, ArmedObject * object, float multiplier);


	~Factory();
};

