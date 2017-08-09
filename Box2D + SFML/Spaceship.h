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

	Statistics basic_stats;
	Statistics current_stats;


	int current_stats_version;


	TimeManager immune_time{ 5.f, false };
	Animation * _animation;
	sf::Shape * _copy_of_shape;

	sf::Color shape_color{ sf::Color::White };


	
	//std::array<Equipment, 6> equipment;


	

	void animationOfReborn(const float & delta);

	void update();
	

public:
	Spaceship(float hp, b2Body * ptr_body, sf::Shape * ptr_shape, 
		float dmg, Statistics statistics);

	Spaceship(b2Body * ptr_body, sf::Shape * ptr_shape, Statistics statistics);

	Statistics getCurrentStats();

	void improveEq(Equipment::Type type);

	~Spaceship();

	// Inherited via Object

	virtual void act(const float & delta) override;
};

