#pragma once
#include "Object.h"
#include "PlayerSerialization.h"


class Player :
	public Object
{

	friend class PlayerSerialization;

private:
	
	const float scale;
	
	const float max_hp{ 1000.f }; // is not final value
	const int max_lives{ 3 };
	const int initial_lives{ 1 };
	const float immunity_after_reborn{ 5.f };
	const float transparency_time{ 0.15f };
	
	
	sf::Color shape_color{ sf::Color::Cyan };
	sf::ConvexShape * _shape;
	b2Body * _body;
	int amount_of_lives;
	float hp;
	
	float time_after_death{ 0.f };
	bool is_immune{ true };



	void animationOfReborn(const float & delta);



public:
	Player(const float & scl, b2Body * ptr_body, sf::ConvexShape * ptr_shape);
	~Player();

	virtual b2Body * getBody() override;

	virtual void hit(const float & dmg) override;
	
	virtual void act(const float & delta) override;
	
	virtual sf::ConvexShape * getShape() override;
	
	virtual bool isDestroyed() override;
	
	virtual sf::Vector2f getPosition() override;
	
	virtual bool isReadyToRemove() override;
};

