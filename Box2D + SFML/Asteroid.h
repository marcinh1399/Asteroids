#pragma once


#include "Object.h"
#include "SFML\Graphics.hpp"
#include <cmath>


#define SCALE 20
#define M_PI 3.14159265359

class Asteroid :
	public Object
{

private :

	float scale;
	float stamina;
	float time_after_impact{ 0.f };
	const float time_of_explosion{ 1.f };
	float time_after_creation{ 0.f };
	bool destroyed{ false };
	bool exploded{ false };
	sf::Vector2f position{ 0.f, 0.f };
	sf::ConvexShape * _shape;
	b2Body * _body;


	inline float radiansToDegrees(float);

	virtual void hit(const float & dmg) override;

	virtual bool isDestroyed() override;
	
	void updatePosition();
	
	Asteroid(float hp, float scl, b2Body * ptr_body, sf::ConvexShape * _shape);

public:

	virtual b2Body * getBody() override;

	virtual sf::ConvexShape * getShape() override;

	virtual void act(const float & delta) override;

	virtual bool isReadyToRemove() override;

	virtual sf::Vector2f getPosition() override;

	~Asteroid();

	friend class AsteroidBuilder;
};






