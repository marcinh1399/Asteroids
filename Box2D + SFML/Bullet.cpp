#include "stdafx.h"
#include "Bullet.h"





void Bullet::updatePosition()
{
	position = Coords::translate(_body->GetPosition());
	_shape->setPosition(position);
}

Bullet::Bullet(sf::Vector2f pos, sf::Shape * ptr_shape, b2Body * ptr_body)
	: position{ pos },  _shape{ ptr_shape }, _body{ptr_body} {}

float Bullet::getDamage()
{
	return damage;
}

Bullet::~Bullet()
{
	delete _shape;
}

b2Body * Bullet::getBody()
{
	return _body;
}

void Bullet::hit(const float & dmg)
{
	collision = true;
}

void Bullet::act(const float & delta)
{
	if (collision)
	{
		time_after_impact += delta;
	}

	updatePosition();

	if (time_after_impact >= time_of_explosion)
	{
		destroyed = true;
	}
}

sf::Shape * Bullet::getShape()
{
	return _shape;
}

bool Bullet::isDestroyed()
{
	return destroyed;
}

sf::Vector2f Bullet::getPosition()
{
	return position;
}

bool Bullet::isReadyToRemove()
{
	return true;
}
