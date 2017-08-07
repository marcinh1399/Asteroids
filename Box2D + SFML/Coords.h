#pragma once
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>

class Coords
{

public:
	static float to_screen;
	static float to_world;
	static float m_pi;


	static void init(float scale_to_screen);

	static b2Vec2 translate(const sf::Vector2f & coord);

	static sf::Vector2f translate(const b2Vec2 & coord);

	static float lengthToWorld(const float & length);

	static float lengthToScreen(const float & length);

	static float radians(const float & deegres);

	static float deegres(const float & radians);

	static b2Vec2 * translateShape(sf::Vector2f shape[], size_t vertices);

	static sf::Vector2f * translateShape(b2Vec2 shape[], size_t vertices);

	static b2PolygonShape translateShape(sf::Shape * _shape);
};

