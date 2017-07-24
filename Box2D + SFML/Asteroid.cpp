

#include "stdafx.h"
#include "Asteroid.h"


inline float Asteroid::radiansToDegrees(float radians)
{
	return radians * 180.f / M_PI;
}

void Asteroid::setStamina()
{
	stamina = _body->GetMass();
}

b2Body * Asteroid::getBody()
{
	return _body;
}

void Asteroid::hit(const float & dmg)
{
	stamina -= dmg;
	if (stamina <= 0) {
		stamina = 0;
		destroyed = true;
	}
}

void Asteroid::act(const float & delta)
{
	if (destroyed)
		time_after_impact += delta;

	if (time_after_impact >= time_of_explosion)
		exploded = true;
}

sf::Sprite & Asteroid::getSprite()
{
	return *_sprite;
}

bool Asteroid::isDestroyed()
{
	return exploded;
}

void Asteroid::updatePosition()
{
	float angle = radiansToDegrees(_body->GetAngle());
	position.x = _body->GetPosition().x * SCALE;
	position.y = _body->GetPosition().y * SCALE;
	_sprite->setPosition(position);
	_sprite->setRotation(angle);
}

Asteroid::Asteroid(b2Body * ptr_body, sf::Sprite * ptr_sprite) :
	_body(ptr_body), _sprite(ptr_sprite)
{
	setStamina();
	updatePosition();
}


Asteroid::~Asteroid()
{
	delete _sprite;
}






