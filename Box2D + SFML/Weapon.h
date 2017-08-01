#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

class Weapon
{
private:

	sf::ConvexShape * _shape;
	b2Body * _body;


public:
	Weapon(sf::Vector2f pos);




	~Weapon();
};

