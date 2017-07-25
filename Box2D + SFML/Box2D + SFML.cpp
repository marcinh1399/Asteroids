#include "stdafx.h"
#include <stdio.h>
#include <cstdlib>
#include "Box2D\Box2D.h"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "AsteroidBuilder.h"
#include "Asteroid.h"
#include "Object.h"
#include <algorithm>
#include <cmath>
#include <memory>
#include "AsteroidGenerator.h"
#include <vector>


#define NDEBUG


#define M_PI 3.14159265359


int main(int argc, char** argv)
{

	srand(time(NULL));

	std::unique_ptr<sf::RenderWindow> _window(new sf::RenderWindow(sf::VideoMode(1920, 1200, 32), "Asteroids!", sf::Style::Fullscreen));
	std::unique_ptr<b2World> _world(new b2World(b2Vec2{ 0.f, 0.f }));

	AsteroidGenerator * _generator = new AsteroidGenerator(_world, 1920, 1200);
	/*
	_generator->makeAsteroid();
	Asteroid * _asteroid1 = _generator->getAsteroid();
	_generator->makeAsteroid();
	Asteroid * _asteroid2 = _generator->getAsteroid();
	_generator->makeAsteroid();
	Asteroid * _asteroid3 = _generator->getAsteroid();
	*/
	std::vector<Asteroid *> v;


	for (int i = 0; ; ++i)
	{
		
		sf::Clock clock;
		clock.restart();
		sf::Time time = sf::seconds(1.f / 60.f);
		while (clock.getElapsedTime() < time);

		_generator->makeAsteroid();
		v.push_back(_generator->getAsteroid());
		



		_world->Step(1.f / 60.f, 8, 3);
		//printf("(%f.6, %f.6)\n", _asteroid1->getBody()->GetPosition().x, _asteroid1->getBody()->GetPosition().y);
		//printf("(%f.6, %f.6)\n", _asteroid2->getBody()->GetPosition().x, _asteroid2->getBody()->GetPosition().y);
		
		_window->clear();

		for (auto * _asteroid : v)
		{
			_asteroid->act(1.f / 60.f);
			sf::ConvexShape s = *_asteroid->getShape();
			_window->draw(s);
		}

		_window->display();
	}



	while (true);
	

#ifndef NDEBUG




	srand(time(NULL));

	int min_radius = 100;
	int rnd_radius = 100;
	int min_vertices = 4;
	int rnd_vertices = 6;
	float omega = 0.01f;


	while (true) {
		int amount_of_vertices = rand() % rnd_vertices + min_vertices;
		int angle_range = 360 / amount_of_vertices;

		for (int i = 0; i < amount_of_vertices; ++i)
		{
			int length = min_radius + rand() % rnd_radius;
			int angle = rand() % angle_range + i * angle_range;
			float radians = angle * M_PI / 180.f;
			float x = sinf(radians) * length;
			float y = cosf(radians) * length;


			printf("%f\n", x*x + y*y);

			#ifndef NDEBUG

			float xxyy = x*x + y*y;
			float max_length = (min_radius + rnd_radius - 1)*(min_radius + rnd_radius - 1) + omega;

			#endif // !NDEBUG


			assert(xxyy <= max_length);


			printf("vertex = (%f, %f)\n", x, y);
		}
	}

#endif // !1

	return 0;
}
