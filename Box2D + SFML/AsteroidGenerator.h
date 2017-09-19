#pragma once
#include "Asteroid.h"
#include <memory>
#include <cmath>
#include "Coords.h"
#include <utility>
#include "World.h"



class AsteroidGenerator
{

private:

	int world_width;
	int world_height;

	const int min_speed{ 700 };
	const int rnd_speed{ 1300 };
	const int div_speed{ 100 };

	const int max_radians_per_second{ 300 };
	const int div_radians_per_second{ 100 };

	const int min_vertices{ 4 };
	const int rnd_vertices{ 4 };

	const int min_radius{ 50 };
	const int rnd_radius{ 70 };

	const sf::Color outline_color{ sf::Color::White };
	const sf::Color fill_color{ sf::Color::Transparent };
	const int outline_thickness{ 3 };

	const int min_density{ 500 };
	const int rnd_density{ 700 };
	const int div_density{ 100 };

	const int min_friction{ 35 };
	const int rnd_friction{ 50 };
	const int div_friction{ 100 };

	const int min_restitution{ 35 };
	const int rnd_restitution{ 30 };
	const int div_restitution{ 100 };


public:

	AsteroidGenerator() = default;

	sf::ConvexShape * makeShape();
	
	sf::Vector2f getSFposition();
	
	b2Vec2 getLinearVelocity(sf::Vector2f position);

	float getAngularVelocity();

	float getDensity();

	float getFriction();

	float getRestitution();

};
