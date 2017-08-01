#pragma once
#include "SFML\Graphics.hpp"


class WeaponShapes
{
	
private:
	
	const float radius = 5;

	sf::CircleShape * _bullet;
	sf::ConvexShape * _rocket;
	sf::RectangleShape * _obstacle;
	

	void loadShapes();


public:

	WeaponShapes();

	sf::CircleShape * getBulletShape();

	sf::ConvexShape * getRocketShape();

	sf::RectangleShape * getObstacleShape();


	~WeaponShapes();
};

