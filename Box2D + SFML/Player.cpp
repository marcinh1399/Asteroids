#include "stdafx.h"
#include "Player.h"


void Player::animationOfReborn(const float & delta)
{
	time_after_death += delta;
	
	int turn = time_after_death / transparency_time;

	if (turn % 2 == 0)
	{
		_shape->setOutlineColor(sf::Color::Transparent);
	}
	else
	{
		_shape->setOutlineColor(shape_color);
	}

	if (time_after_death > immunity_after_reborn)
	{
		is_immune = false;
		time_after_death = 0.f;
		_shape->setOutlineColor(shape_color);
	}
}


Player::Player(const float & scl, b2Body * ptr_body, sf::ConvexShape * ptr_shape)
	: scale(scl), _body(ptr_body), _shape(ptr_shape) {}

Player::~Player()
{
	delete _shape;
}

b2Body * Player::getBody()
{
	return _body;
}

void Player::hit(const float & dmg)
{
	hp -= dmg;

	if (dmg < 0)
	{
		hp = max_hp;
		--amount_of_lives;

		if (amount_of_lives == 0)
		{
			/// animation of game end
		}
		else
		{
			is_immune = true;
		}

	}
}

void Player::act(const float & delta)
{
	if (is_immune)
	{
		animationOfReborn(delta);
	}

}

sf::ConvexShape * Player::getShape()
{
	return _shape;
}

bool Player::isDestroyed()
{
	return false;
}

sf::Vector2f Player::getPosition()
{
	return sf::Vector2f();
}

bool Player::isReadyToRemove()
{
	return false;
}
