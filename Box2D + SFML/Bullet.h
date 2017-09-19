#pragma once
#include "Object.h"

class Object;

class Bullet :
	public Object
{

public:

	enum class Type
	{
		bullet,
		rocket,
		obstacle
	};

	Bullet(b2Body * ptr_body, sf::Shape * ptr_shape, float hp);

	virtual ~Bullet();

	// Inherited via Object
	virtual void act(const float & delta) override;
};

