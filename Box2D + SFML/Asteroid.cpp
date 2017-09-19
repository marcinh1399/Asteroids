#include "stdafx.h"
#include "Asteroid.h"




Asteroid::Asteroid(b2Body * body, sf::Shape * shape)
	: Object(body, shape)
{
	_body->SetUserData(this);
	updatePosition();
}

Asteroid::~Asteroid()
{
}

void Asteroid::act(const float & delta)
{
	updatePosition();

	if (state == ObjectState::created)
	{
		if (create_time.isReady())
		{
			state = ObjectState::alive;
		}
		else
		{
			create_time += delta;
		}
	}
}
