#include "stdafx.h"
#include "Bullet.h"



Bullet::Bullet(float hp, b2Body * ptr_body, sf::Shape * ptr_shape, float dmg)
	: Object(hp, ptr_body, ptr_shape, dmg)
{
	_body->SetUserData(this);
	state = ObjectState::alive;
}

void Bullet::act(const float & delta)
{
	updatePosition();
}



