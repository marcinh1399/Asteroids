

#include "stdafx.h"
#include "Asteroid.h"


inline float Asteroid::radiansToDegrees(float radians)
{
	return radians * 180.f / M_PI;
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
	time_after_creation += delta;

	if (destroyed)
		time_after_impact += delta;

	updatePosition();

	if (time_after_impact >= time_of_explosion)
		exploded = true;
}

bool Asteroid::isReadyToRemove()
{
	return time_after_creation > 4.f;
}

sf::Vector2f Asteroid::getPosition()
{
	return position;
}

sf::ConvexShape * Asteroid::getShape()
{
	return _shape;
}

bool Asteroid::isDestroyed()
{
	return exploded;
}

void Asteroid::updatePosition()
{
	float angle = radiansToDegrees(_body->GetAngle());
	position.x = _body->GetPosition().x * scale;
	position.y = _body->GetPosition().y * scale;
	_shape->setPosition(position);
	_shape->setRotation(angle);
}

Asteroid::Asteroid(float hp, float scl, b2Body * ptr_body, sf::ConvexShape * ptr_shape) 
	: stamina(hp), scale(scl), _body(ptr_body), _shape(ptr_shape)
{
	_body->SetUserData(this);
	updatePosition();
}



Asteroid::~Asteroid()
{
	delete _shape;
}






