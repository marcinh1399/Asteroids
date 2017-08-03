#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "BulletShapes.h"
#include "Bullet.h"
#include "Player.h"
#include <memory>
#include "Coords.h"
#include <cmath>

class BulletBuilder
{
private:
	Player * _player;
	std::unique_ptr<b2World> & _world;
	BulletShapes * _shapes;


// CONST VALUES -- Possible changes
	const int group_of_player_body{ 0 }; // ???

	const float density{ 50.f };
	const float friction{ 0.5f };
	const float restitution{ 0.2f };
	const float speed_of_bullet{ 10.f };
	const float speed_of_rocket{ 7.5f }; // maybe in future I'll add acceleration

// END OF CONST VALUES

	sf::Vector2f screen_position;
	b2Vec2 world_position;
	
	void setPosition();

	b2Body * setBody(sf::Shape * _shape);

	b2Body * setCircleBody(sf::CircleShape * _shape);

	b2Vec2 getSpeed(const float & speed);

public:
	BulletBuilder(Player * ptr_player, std::unique_ptr<b2World> & u_world);

	Bullet * makeBullet();

	Bullet * makeRocket();

	Bullet * makeObstacle();

	~BulletBuilder();
};
