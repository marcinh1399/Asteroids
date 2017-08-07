#include "stdafx.h"
#include "Asteroid.h"



Asteroid::Asteroid(float hp, b2Body * ptr_body, sf::Shape * ptr_shape, float dmg)
	: Object(hp, ptr_body, ptr_shape, dmg)
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






