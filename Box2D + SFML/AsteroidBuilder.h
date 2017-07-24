#pragma once

#include "Box2D\Box2D.h"
#include "SFML\Graphics.hpp"
#include "Asteroid.h"
#include <cstdlib>
#include <vector>

#define M_PI 3.14159265359
#define SCALE 0.5
#define MIN_DENSITY 50
#define RND_DENSITY	50
#define SCL_DENSITY 0.1
#define MIN_FRICTION 35
#define RND_FRICTION 50
#define SCL_FRICTION 0.01


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

	

	b2Body * generateBody(const float & x, const float & y);

	sf::ConvexShape * generateSFShape(const int & amount);

	void resizeToB2(int amount);

	float randDensity();

	float randFriction();
	

public:
	AsteroidBuilder(int max_radius, b2World * ptr_world);
	
	Asteroid * getNewAsteroid(const float & xWorld, const float & yWorld);

	~AsteroidBuilder();
};

