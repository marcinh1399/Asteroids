#include "stdafx.h"
#include "Object.h"



Object::~Object()
{
	delete _shape;
}

void Object::updatePosition()
{
	_shape->setPosition(Coords::translate(_body->GetPosition()));
	_shape->setRotation(Coords::deegres(_body->GetAngle()));
}

Object::Object(b2Body * body, sf::Shape * shape)
	: Subject(),
	_body(body),
	_shape(shape)
{
	damage = stamina = body->GetMass();
	state = ObjectState::created;
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

sf::Vector2f Object::getSFposition()
{
	return _shape->getPosition();
}

b2Vec2 Object::getB2position()
{
	return _body->GetPosition();
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


float Object::getRadius()
{
	return Coords::lengthToWorld(_shape->getLocalBounds().height / 2);
}
