#include "stdafx.h"
#include "Bullet.h"




Bullet::Bullet(b2Body * ptr_body, sf::Shape * ptr_shape, float hp)
	: Object(ptr_body, ptr_shape)
{
	damage = stamina = hp;
	_body->SetUserData(this);
	state = ObjectState::alive;
}

void Bullet::act(const float & delta)
{
	updatePosition();
}



