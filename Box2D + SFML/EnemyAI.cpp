#include "stdafx.h"
#include "EnemyAI.h"




EnemyAI::EnemyAI(b2Body * body, sf::Shape * shape, Statistics statistics, std::map<b2Body *, Object *> & objects)
	: AIObject(body, shape, statistics, objects)
{
}

EnemyAI::~EnemyAI()
{
}

void EnemyAI::act(const float & delta)
{
	this->update(delta);

	this->updateMissileManager(delta);

	updatePosition();

	notifyObservers();
}
