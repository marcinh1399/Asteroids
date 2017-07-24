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
	sf::Sprite * _sprite;
	b2Body * _body;



	inline float radiansToDegrees(float);

	void setStamina();

	virtual b2Body * getBody() override;

	virtual void hit(const float & dmg) override;

	virtual void act(const float & delta) override;

	virtual sf::Sprite & getSprite() override;

	virtual bool isDestroyed() override;
	
	void updatePosition();
	


public:
	Asteroid(b2Body * ptr_body, sf::Sprite * ptr_sprite);

	~Asteroid();
};






