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

constexpr float Coords::radians(const float & deegres)
{
	return deegres * m_pi / 180.;
}

constexpr float Coords::deegres(const float & radians)
{
	return radians * 180.f / m_pi;
}
