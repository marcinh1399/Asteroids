#pragma once
#include "Box2D\Box2D.h"
#include "SFML\Graphics.hpp"
#include "Asteroid.h"
#include <cstdlib>
#include <vector>
#include <memory>
#include "Tests.h"
#include "Coords.h"


#define MIN_DENSITY 50
#define RND_DENSITY	50
#define SCL_DENSITY 0.1
#define MIN_FRICTION 35
#define RND_FRICTION 50
#define SCL_FRICTION 0.01
#define MIN_SPEED 50
#define RND_SPEED 50


class AsteroidBuilder
{

private:

	int min_radius;
	int rnd_radius;
	const int min_vertices = 4;
	const int rnd_vertices = 4;
	std::unique_ptr<b2World> & _world;
	b2Vec2 * b2_vertices;
	sf::Vector2f * sf_vertices;


	float stamina;
	int amount_of_vertices;
	sf::ConvexShape * _shape;
	b2Vec2 world_position{ 0.f, 0.f };
	sf::Vector2f screen_position{ 0.f, 0.f };
	b2Body * _body;


	AsteroidBuilder * setWorldPosition(b2Vec2 position);

	AsteroidBuilder * setScreenPosition(sf::Vector2f position);

	AsteroidBuilder * setSfmlShape();

	AsteroidBuilder * setBox2DShape();

	AsteroidBuilder * setBody();

	AsteroidBuilder * setStamina();

	AsteroidBuilder * setLinearVelocity(b2Vec2 v);

	AsteroidBuilder * setAngularVelocity(float angle);

	Asteroid * build();



	void setRangeOfRadius(const int & radius);

	float randDensity();

	float randFriction();
	

public:
	AsteroidBuilder(int max_radius, std::unique_ptr<b2World> & unique_world);

	~AsteroidBuilder();

	friend class AsteroidGenerator;

};


