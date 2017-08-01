#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <Box2D\Box2D.h>
#include "Equipment.h"

class Spaceship
{

private:

	struct Stats
	{
		unsigned int hp;
		unsigned int speed;
		unsigned int radians_per_second;
		unsigned int basic_armor;
		unsigned int basic_damage_of_bullets;
		unsigned int basic_bullet_cooldown;
	};

	sf::ConvexShape shape;

	Stats stats;

	sf::Vector2f position;
	b2Body * _body;
	
	///Equipment
	/*
	
	Armor * _armor;
	Bullet * _bullet;
	Engine * _engine;
	Agility * _agility;
	
	*/
	

public:
	Spaceship();


	~Spaceship();
};

