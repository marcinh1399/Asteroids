#pragma once

#include "Box2D\Box2D.h"
#include "SFML\Graphics.hpp"
#include <cstdlib>
#include <vector>

#define M_PI 3.14159265359
#define SCALE 0.5


class AsteroidBuilder
{

private:
	int min_radius;
	int rnd_radius;
	const int min_vertices = 4;
	const int rnd_vertices = 4;

	b2World * _world;

	b2Vec2 * b2_vertices;
	sf::Vector2f * sf_vertices;

	void setRangeOfRadius(const int & radius);

	int generateShape();

	void resizeToB2(int amount);
	

public:
	AsteroidBuilder(int max_radius, b2World * ptr_world);
	
	

	~AsteroidBuilder();
};

