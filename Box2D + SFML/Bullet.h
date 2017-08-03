#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Object.h"
#include "Coords.h"

class Bullet
	: public Object
{
private:

	sf::Shape * _shape;
	b2Body * _body;
	sf::Vector2f position;
	float damage;

	float time_after_impact{ 0.f };
	const float time_of_explosion{ 1.f };

	bool collision{ false };
	bool destroyed{ false };


	void updatePosition();


public:
	Bullet(sf::Vector2f pos, sf::Shape * ptr_shape, b2Body * ptr_body);

	float getDamage();

	virtual b2Body * getBody() override;

	virtual void hit(const float & dmg) override;

	virtual void act(const float & delta) override;

	virtual sf::Shape * getShape() override;

	virtual bool isDestroyed() override;

	virtual sf::Vector2f getPosition() override;

	virtual bool isReadyToRemove() override;

	~Bullet();

};

