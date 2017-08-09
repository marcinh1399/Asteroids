#include "stdafx.h"
#include "AsteroidGenerator.h"


AsteroidGenerator::AsteroidGenerator(int width, int height)
{
	world_width = width;
	world_height = height;
}


sf::ConvexShape * AsteroidGenerator::makeShape()
{
	size_t number_of_vertices = rand() % rnd_vertices + min_vertices;
	
	float f_angle = 360 / number_of_vertices;
	int angle = static_cast<int>(f_angle);

	sf::ConvexShape * shape = new sf::ConvexShape(number_of_vertices);

	for (int i = 0; i < number_of_vertices; ++i)
	{
		int alpha = Coords::radians(f_angle * i + rand() % angle);
		int length = min_radius + rand() % rnd_radius;
		shape->setPoint(i, sf::Vector2f( sin(alpha) * length, cos(alpha) * length ));
	}

	shape->setOutlineThickness(outline_thickness);
	shape->setOutlineColor(outline_color);
	shape->setFillColor(fill_color);

	return shape;
}

sf::Vector2f AsteroidGenerator::getPosition()
{
	int side_of_screen = rand() % 4;
	int x, y;

	switch (side_of_screen)
	{
		case 0:
			x = rand() % (world_width + 400) - 200;
			y = -200;
			break;
		case 1:
			x = world_width + 200;
			y = rand() % (world_width + 400) - 200;
			break;
		case 2:
			x = rand() % (world_width + 400) - 200;
			y = world_height + 200;
			break;
		case 3:
			x = -200;
			y = rand() % (world_height + 400) - 200;
			break;
	}

	return sf::Vector2f(x, y);
}

b2Vec2 AsteroidGenerator::getLinearVelocity(sf::Vector2f position)
{
	float speed = ((rand() % rnd_speed) + min_speed) / static_cast<float>(div_speed);

	int offset = 100;
	int x_range = world_width - 2 * offset;
	int y_range = world_height - 2 * offset;

	int x = rand() % x_range + offset;
	int y = rand() % y_range + offset;

	int delta_x = position.x - x;
	int delta_y = position.y - y;

	float distance = sqrt(delta_x * delta_x + delta_y * delta_y);

	float scale = -(speed / distance);

	return b2Vec2(delta_x * scale, delta_y * scale);
}

float AsteroidGenerator::getAngularVelocity()
{
	return (rand() % max_radians_per_second) / static_cast<float>(div_radians_per_second);
}

float AsteroidGenerator::getDensity()
{
	return (rand() % rnd_density + min_density) / static_cast<float>(div_density);
}

float AsteroidGenerator::getFriction()
{
	return (rand() % rnd_friction + min_friction) / static_cast<float>(div_friction);
}

float AsteroidGenerator::getRestitution()
{
	return (rand() % rnd_restitution + min_restitution) / static_cast<float>(div_restitution);
}
