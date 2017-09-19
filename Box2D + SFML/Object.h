#pragma once
#include "Subject.h"
#include "Box2D\Box2D.h"
#include "SFML\Graphics.hpp"
#include "Coords.h"


class Object :
	public Subject
{

protected:
	b2Body * _body;
	sf::Shape * _shape;
	ObjectState state;

	float stamina;
	float damage;

	void updatePosition();

public:
	
	Object(b2Body * body, sf::Shape * shape);

	b2Body * getBody();

	sf::Shape * getShape();

	ObjectState getState();

	sf::Vector2f getSFposition();

	b2Vec2 getB2position();

	float getDamage();

	bool hit(const float & damage); // Returns true if object has been destroyed

	virtual void act(const float & delta) = 0;

	float getRadius();

	virtual ~Object();
};

