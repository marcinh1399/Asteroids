#include "stdafx.h"
#include "Enemy.h"





Enemy::Enemy(b2Body * body, sf::Shape * shape, Statistics statistics, std::shared_ptr<GameObjects> g_objects)
	: Object(body, shape)
{
	body->SetUserData(this);
	stats = statistics;
	ai = new AI(g_objects, this);
}

Statistics Enemy::getStats()
{
	return stats;
}

b2Vec2 Enemy::frontOfShip()
{
	auto transform = getShape()->getTransform();
	auto point_pos = transform.transformPoint(getShape()->getPoint(0));

	return Coords::translate(point_pos);
}

b2Vec2 Enemy::backOfShip()
{
	auto transform = getShape()->getTransform();
	auto point_pos = transform.transformPoint(getShape()->getPoint(2));

	return Coords::translate(point_pos);
}

Enemy::~Enemy()
{
	delete ai;
}

void Enemy::act(const float & delta)
{
	ai->act(delta);

	updatePosition();
}
