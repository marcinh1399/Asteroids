#pragma once
#include "Box2D\Box2D.h"
#include "Object.h"

class Body :
	public b2Body
{
private:
	
	Object * _owner;


public:
	Body(Object * ptr_owner);

	~Body();
};

