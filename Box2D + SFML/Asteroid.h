#pragma once
#include "Object.h"
#include "TimeManager.h"

class Asteroid :
	public Object
{

private:

	TimeManager create_time{ 6.f, false };

public:

	Asteroid(b2Body * body, sf::Shape * shape);

	virtual ~Asteroid();

	// Inherited via Object
	virtual void act(const float & delta) override;
};

