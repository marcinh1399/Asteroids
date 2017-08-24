#pragma once
#include "Object.h"
#include "AI.h"
#include "GameObjects.h"
#include "Statistics.h"
#include <Box2D\Box2D.h>


class AI;
class GameObjects;


class Enemy :
	public Object
{

private:

	AI * ai;

	Statistics stats;


public:
	Enemy(b2Body * body, sf::Shape * shape, Statistics statistics, std::shared_ptr<GameObjects> g_objects);

	Statistics getStats();

	b2Vec2 frontOfShip();

	b2Vec2 backOfShip();

	~Enemy();

	// Inherited via Object
	virtual void act(const float & delta) override;
};

