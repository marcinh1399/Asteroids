#include "stdafx.h"
#include "WeaponShapes.h"


void WeaponShapes::loadShapes()
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

WeaponShapes::WeaponShapes()
{
	loadShapes();
}

sf::CircleShape * WeaponShapes::getBulletShape()
{
	return new sf::CircleShape(*_bullet);
}

sf::ConvexShape * WeaponShapes::getRocketShape()
{
	return new sf::ConvexShape(*_rocket);
}

sf::RectangleShape * WeaponShapes::getObstacleShape()
{
	return new sf::RectangleShape(*_obstacle);
}


WeaponShapes::~WeaponShapes()
{
	delete _bullet;
	delete _rocket;
	delete _obstacle;
}
