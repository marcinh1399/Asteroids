#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <Box2D\Box2D.h>
#include "Equipment.h"
#include <array>
#include "Statistics.h"
#include "Object.h"
#include "TimeManager.h"
#include "IListener.h"
#include <memory>

class Spaceship
	: public Object, IListener
{

private:

	Statistics current_stats;


	TimeManager immune_time{ 5.f, false };
	Animation * _animation;
	sf::Shape * _copy_of_shape;

	sf::Color shape_color{ sf::Color::White };


	void animationOfReborn(const float & delta);

	// Inherited via IListener
	virtual void handling(const float & delta) override;

	void linearVelocity(const float & delta, int move);

	void angularVelocity(const float & delta, int turn);





	// init functions

	void immuneAnimation();

	void setKeys();

	//


public:


	Spaceship(b2Body * ptr_body, sf::Shape * ptr_shape, 
		Statistics statistics, std::shared_ptr<KeyboardHandling> keyboard_handling);

	Statistics getCurrentStats();

	~Spaceship();

	// Inherited via Object

	virtual void act(const float & delta) override;


};

