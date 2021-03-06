#include "stdafx.h"
#include "AsteroidGenerator.h"





sf::ConvexShape * AsteroidGenerator::makeShape()
{
	size_t number_of_vertices = rand() % rnd_vertices + min_vertices;
	
	float f_angle = 360.f / number_of_vertices;
	int angle = static_cast<int>(f_angle);
	
	auto shape = new sf::ConvexShape(number_of_vertices);

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

sf::Vector2f AsteroidGenerator::getSFposition()
{
	return World::asteroidStartingPosition();
}

b2Vec2 AsteroidGenerator::getLinearVelocity(sf::Vector2f position)
{
	float speed = ((rand() % rnd_speed) + min_speed) / static_cast<float>(div_speed);

	auto v = World::asteroidDestPosition();

	int delta_x = position.x - v.x;
	int delta_y = position.y - v.y;

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
