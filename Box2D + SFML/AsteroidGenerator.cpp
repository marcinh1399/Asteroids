#include "stdafx.h"
#include "AsteroidGenerator.h"


sf::Vector2f AsteroidGenerator::getRandomScreenPosition()
{
	int side_of_screen = rand() % 4;
	int x, y;

	switch (side_of_screen)
	{
		case 0:	
			y = -100; 
			x = rand() % (screen_width + 200) - 100;
			break;
		case 1: 
			x = screen_width + 100;
			y = rand() % (screen_height + 200) - 100;
			break;
		case 2: 
			y = screen_height + 100;
			x = rand() % (screen_width + 200) - 100; 
			break;
		case 3: 
			x = -100;
			y = rand() % (screen_height + 200) - 100; 
			break;
	}

	return sf::Vector2f(x, y);
}


b2Vec2 AsteroidGenerator::getRandomLinearVelocity(sf::Vector2f position)
{
	float speed = (rand() % rnd_speed + min_speed) / 200;

	int offset = 250;
	int x_range = screen_width - 2 * offset;
	int y_range = screen_height - 2 * offset;

	int x = rand() % x_range + offset;
	int y = rand() % y_range + offset;

	int delta_x = position.x - x;
	int delta_y = position.y - y;

	float distance = sqrt(delta_x * delta_x + delta_y * delta_y);

	float speed_scale = speed / distance;

	return b2Vec2(-delta_x * speed_scale, -delta_y * speed_scale);
}

float AsteroidGenerator::getRandomAngularVelocity()
{
	return Coords::radians(rand() % rnd_angle_per_second + min_angle_per_second);
}

AsteroidGenerator::AsteroidGenerator(std::unique_ptr<b2World>& _world, int screen_width, int screen_height)
{
	this->screen_width = screen_width;
	this->screen_height = screen_height;
	_builder = new AsteroidBuilder(100, _world);
}

Asteroid * AsteroidGenerator::makeAsteroid()
{
	sf::Vector2f screen_position = getRandomScreenPosition();
	b2Vec2 world_position = Coords::translate(screen_position);
	float angular_velocity = getRandomAngularVelocity();
	b2Vec2 linear_velocity = getRandomLinearVelocity(screen_position);

	Asteroid * _asteroid = _builder
		->setWorldPosition(world_position)
		->setScreenPosition(screen_position)
		->setSfmlShape()
		->setBox2DShape()
		->setBody()
		->setStamina()
		->setAngularVelocity(angular_velocity)
		->setLinearVelocity(linear_velocity)
		->build();

	return _asteroid;
}


AsteroidGenerator::~AsteroidGenerator()
{
}
