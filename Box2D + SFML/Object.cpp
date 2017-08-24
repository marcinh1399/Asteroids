#include "stdafx.h"
#include "Object.h"


Object::Object(float hp, b2Body * body, sf::Shape * shape, float dmg)
	: stamina{ hp }, 
	_body{ body }, 
	_shape{ shape }, 
	damage{ dmg }
{
	state = ObjectState::created;
}

Object::Object(b2Body * body, sf::Shape * shape)
	: _body(body),
	_shape(shape)
{
	damage = stamina = body->GetMass();
	state = ObjectState::created;
}

Object::~Object()
{
	delete _shape;
}

float Object::getRadius()
{
	return Coords::lengthToWorld(_shape->getLocalBounds().height / 2);
}

b2Body * Object::getBody()
{
	return _body;
}

sf::Shape * Object::getShape()
{
	return _shape;
}

ObjectState Object::getState()
{
	return state;
}

sf::Vector2f Object::getPosition()
{
	return _shape->getPosition();
}

float Object::getDamage()
{
	return damage;
}

bool Object::hit(const float & damage)
{
	bool destroyed{ false };

	if (state != ObjectState::immune)
	{
		stamina -= damage;

		if (stamina <= 0)
		{
			stamina = 0;
			state = ObjectState::dead;
			destroyed = true;
		}
	}

	return destroyed;
}


void Object::updatePosition()
{
	_shape->setPosition(Coords::translate(_body->GetPosition()));
	_shape->setRotation(Coords::deegres(_body->GetAngle()));
}
