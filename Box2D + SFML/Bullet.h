#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Object.h"
#include "Coords.h"
#include "TimeManager.h"

class Bullet
	: public Object
{


public:

	enum class Type
	{
		bullet,
		rocket,
		obstacle
	};


	//New Constructor
	Bullet(b2Body * ptr_body, sf::Shape * ptr_shape, float hp);



	// Inherited via Object
	virtual void act(const float & delta) override;

};

