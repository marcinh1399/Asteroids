#pragma once
#include "AsteroidBuilder.h"
#include "Asteroid.h"
#include <memory>
#include <cmath>
#include "Coords.h"


class AsteroidGenerator
{

private:
	int screen_width;
	int screen_height;
	const int min_speed = 1000;
	const int rnd_speed = 3000;
	const int min_angle_per_second = 30;
	const int rnd_angle_per_second = 150;


	AsteroidBuilder * _builder;

	sf::Vector2f getRandomScreenPosition();

	b2Vec2 getRandomLinearVelocity(sf::Vector2f position);

	float getRandomAngularVelocity();
	


public:
	AsteroidGenerator(std::unique_ptr<b2World> & _world, int screen_width, int screen_height);

	Asteroid * makeAsteroid();

	~AsteroidGenerator();


};

