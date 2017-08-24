#pragma once

#include "Box2D\Box2D.h"
#include "SFML\Graphics.hpp"
#include "Coords.h"
#include "ObjectState.h"
#include "TimeManager.h"
#include "Animation.h"


class Object
{

protected:
	b2Body * _body;
	sf::Shape * _shape;
	ObjectState state;

	float stamina;
	float damage;

	void updatePosition();

public:

	Object(float hp, b2Body * body, sf::Shape * shape, float dmg);

	Object(b2Body * body, sf::Shape * shape);

	b2Body * getBody();

	sf::Shape * getShape();

	ObjectState getState();

	sf::Vector2f getPosition();
	
	float getDamage();

	bool hit(const float & damage); // Returns true if object has been destroyed

	virtual void act(const float & delta) = 0;

	virtual ~Object();

	float getRadius();
	
};



/*
class Object
{

public:

	virtual b2Body * getBody() = 0;

	virtual void hit(const float & dmg) = 0;

	virtual void act(const float & delta) = 0;

	virtual sf::Shape * getShape() = 0;

	virtual bool isDestroyed() = 0;

	virtual sf::Vector2f getPosition() = 0;

	virtual bool isReadyToRemove() = 0;

};

*/