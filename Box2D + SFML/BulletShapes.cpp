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

sf::Shape * BulletShapes::getShape(Bullet::Type type)
{
	sf::Shape * shape = nullptr;

	switch (type)
	{
	case Bullet::Type::bullet:		shape = new sf::CircleShape(*_bullet);		break;
	case Bullet::Type::rocket:		shape = new sf::ConvexShape(*_rocket);		break;
	case Bullet::Type::obstacle:	shape = new sf::RectangleShape(*_obstacle);	break;
	}

	return shape;
}

float BulletShapes::getSpeed(Bullet::Type type)
{
	float speed = 0.f;

	switch (type)
	{
		case Bullet::Type::bullet:		speed = bullet_speed;	break;
		case Bullet::Type::rocket:		speed = rocket_speed;	break;
		case Bullet::Type::obstacle:	speed = obstacle_speed; break;
	}

	return speed;
}

float BulletShapes::getHP(Bullet::Type type)
{
	float hp = 0.f;

	switch (type)
	{
	case Bullet::Type::bullet:		hp = bullet_hp;		break;
	case Bullet::Type::rocket:		hp = rocket_hp;		break;
	case Bullet::Type::obstacle:	hp = obstacle_hp;	break;
	}

	return hp;
}


BulletShapes::~BulletShapes()
{
	delete _bullet;
	delete _rocket;
	delete _obstacle;
}
