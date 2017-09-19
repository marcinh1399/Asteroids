#pragma once
#include "AIObject.h"
class EnemyAI :
	public AIObject
{

public:


	EnemyAI(b2Body * body, sf::Shape * shape, Statistics statistics, std::map<b2Body *, Object *> & objects);

	~EnemyAI();

	// Inherited via AIObject
	virtual void act(const float & delta) override;
};

