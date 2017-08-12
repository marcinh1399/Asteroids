#pragma once
#include "SFML\Graphics.hpp"
#include <utility>
#include "Bullet.h"


class BulletShapes
{
	
private:
	
	const float radius = 5;

	sf::CircleShape * _bullet;
	sf::ConvexShape * _rocket;
	sf::RectangleShape * _obstacle;


	////			HP			////
	const float bullet_hp{ 150.f };
	const float rocket_hp{ 350.f };
	const float obstacle_hp{ 1000.f };
	////////////////////////////////


	////		SPEED			////
	const float bullet_speed{ 200.f };
	const float rocket_speed{ 120.f };
	const float obstacle_speed{ 0.f };
	////////////////////////////////

	

	void loadShapes();


public:

	BulletShapes();

	sf::Shape * getShape(Bullet::Type type);

	float getSpeed(Bullet::Type type);

	float getHP(Bullet::Type type);

	~BulletShapes();
};

