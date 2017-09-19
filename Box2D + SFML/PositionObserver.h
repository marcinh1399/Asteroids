#pragma once
#include "Observer.h"
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>


class PositionObserver :
	public Observer
{

private:

	b2Vec2 b2position;
	sf::Vector2f sfposition;

public:

	PositionObserver(Object * subject);

	virtual void update() override;

	virtual void getState(State & update) override;

};

