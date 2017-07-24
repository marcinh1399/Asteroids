#pragma once

#include "Box2D\Box2D.h"
#include "SFML\Graphics.hpp"

class Object
{
public:

	virtual b2Body * getBody() = 0;

	virtual void hit(const float & dmg) = 0;

	virtual void act(const float & delta) = 0;

	virtual sf::ConvexShape * getShape() = 0;

	virtual bool isDestroyed() = 0;

};
