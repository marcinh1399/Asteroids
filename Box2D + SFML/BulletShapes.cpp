#include "stdafx.h"
#include "BulletShapes.h"


void BulletShapes::loadShapes()
{
	_bullet = new sf::CircleShape(radius);
	_obstacle = new sf::RectangleShape(sf::Vector2f{ 20, 20 });
	

	sf::Vector2f rocket[5] = {
		sf::Vector2f(0.f, -10.f),
		sf::Vector2f(-5.f, 0.f),
		sf::Vector2f(-5.f, 10.f),
		sf::Vector2f(5.f, 10.f),
		sf::Vector2f(5.f, 0.f)
	};

	_rocket = new sf::ConvexShape(5);

	for (int i = 0; i < 5; ++i)
	{
		_rocket->setPoint(i, rocket[i]);
	}


}

BulletShapes::BulletShapes()
{
	loadShapes();
}

sf::CircleShape * BulletShapes::getBulletShape()
{
	return new sf::CircleShape(*_bullet);
}

sf::ConvexShape * BulletShapes::getRocketShape()
{
	return new sf::ConvexShape(*_rocket);
}

sf::RectangleShape * BulletShapes::getObstacleShape()
{
	return new sf::RectangleShape(*_obstacle);
}


BulletShapes::~BulletShapes()
{
	delete _bullet;
	delete _rocket;
	delete _obstacle;
}
