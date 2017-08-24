#include "stdafx.h"
#include "Coords.h"



void Coords::init(float scale_to_screen)
{
	to_world = 1.f / scale_to_screen;
	to_screen = scale_to_screen;
	m_pi = 3.14159265359f;
}

b2Vec2 Coords::translate(const sf::Vector2f & coord)
{
	return b2Vec2{ coord.x * to_world, coord.y * to_world };
}

sf::Vector2f Coords::translate(const b2Vec2 & coord)
{
	return sf::Vector2f{ coord.x * to_screen, coord.y * to_screen };
}

float Coords::lengthToWorld(const float & length)
{
	return length * to_world;
}

float Coords::lengthToScreen(const float & length)
{
	return length * to_screen;
}

float Coords::radians(const float & deegres)
{
	return deegres * m_pi / 180.;
}

float Coords::deegres(const float & radians)
{
	return radians * 180.f / m_pi;
}

b2Vec2 * Coords::translateShape(sf::Vector2f shape[], size_t vertices)
{
	b2Vec2 * b2_shape = new b2Vec2[vertices];

	for (int i = 0; i < vertices; ++i)
	{
		b2_shape[i] = translate(shape[i]);
	}

	return b2_shape;
}

sf::Vector2f * Coords::translateShape(b2Vec2 shape[], size_t vertices)
{
	sf::Vector2f * sf_shape = new sf::Vector2f[vertices];

	for (int i = 0; i < vertices; ++i)
	{
		sf_shape[i] = translate(shape[i]);
	}

	return sf_shape;
}



std::shared_ptr<b2Shape> Coords::translateShape(sf::Shape * sf_shape)
{
	std::shared_ptr<b2Shape> ptr;

	if (auto sf_circle = dynamic_cast<sf::CircleShape *>(sf_shape))
	{
		ptr = std::make_shared<b2CircleShape>();
		ptr->m_radius = lengthToWorld(sf_circle->getRadius());
	}
	else 
	{
		b2Vec2 * vertices = new b2Vec2[sf_shape->getPointCount()];

		for (int i = 0; i < sf_shape->getPointCount(); ++i)
		{
			vertices[i] = translate(sf_shape->getPoint(i));
		}
		
	
		ptr = std::make_shared<b2PolygonShape>();
		
		std::static_pointer_cast<b2PolygonShape>(ptr)->Set(vertices, sf_shape->getPointCount());
		// sometimes throws exception ^


		delete[] vertices;
	}

	return ptr;
}

sf::Vector2f Coords::centerInPoint(sf::Vector2f v, const sf::Texture * texture, sf::Vector2f scale)
{
	v.x -= scale.x * texture->getSize().x / 2;
	v.y -= scale.y * texture->getSize().y / 2;
	return v;
}
