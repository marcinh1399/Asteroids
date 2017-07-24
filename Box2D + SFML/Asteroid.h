#pragma once


#include "Object.h"
#include "SFML\Graphics.hpp"


#define SCALE 1
#define M_PI 3.14159265359

class Asteroid :
	public Object
{

private :

	float stamina{ INFINITY };
	float time_after_impact{ 0.f };
	const float time_of_explosion{ 1.f };
	bool destroyed{ false };
	bool exploded{ false };
	sf::Vector2f position{ 0.f, 0.f };
	sf::Shape * _shape;
	b2Body * _body;



	inline float radiansToDegrees(float);

	void setStamina();

	

	virtual void hit(const float & dmg) override;

	virtual void act(const float & delta) override;

	virtual sf::Shape & getShape() override;

	virtual bool isDestroyed() override;
	
	void updatePosition();
	


public:
	Asteroid(b2Body * ptr_body, sf::Shape * _shape);

	virtual b2Body * getBody() override;

	~Asteroid();
};






