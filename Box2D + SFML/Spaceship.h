#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <Box2D\Box2D.h>
#include "Equipment.h"
#include <array>
#include "Statistics.h"
#include "Object.h"
#include "TimeManager.h"

class Spaceship
	: public Object
{

private:

	Statistics stats;

	TimeManager immune_time{ 5.f, false };
	Animation * _animation;
	sf::Shape * _copy_of_shape;

	sf::Color shape_color{ sf::Color::White };


	
	std::array<Equipment, 6> equipment;


	void setEq();

	void animationOfReborn(const float & delta);
	

public:
	Spaceship(float hp, b2Body * ptr_body, sf::Shape * ptr_shape, float dmg, Statistics statistics);

	bool improveHP();

	bool improveEngine();

	bool improveAgility();

	bool improveArmor();

	bool improveBullet();

	bool improveGun();

	~Spaceship();

	// Inherited via Object

	virtual void act(const float & delta) override;
};

