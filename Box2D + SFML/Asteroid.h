#pragma once
#include "Coords.h"
#include "Object.h"
#include "SFML\Graphics.hpp"
#include <cmath>
#include "TimeManager.h"


class Asteroid :
	public Object
{

private :

	TimeManager create_time{ 6.f, false };
	
	Asteroid(float hp, b2Body * ptr_body, sf::Shape * _shape, float dmg);

public:

	~Asteroid();

	friend class AsteroidBuilder;

	// Inherited via Object
	virtual void act(const float & delta) override;
};






