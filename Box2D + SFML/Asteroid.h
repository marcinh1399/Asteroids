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

public:

	// New Constructor 
	Asteroid(b2Body * body, sf::Shape * shape);

	~Asteroid();

	// Inherited via Object
	virtual void act(const float & delta) override;
};






