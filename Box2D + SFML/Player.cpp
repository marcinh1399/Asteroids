#include "stdafx.h"
#include "Player.h"




Player::~Player()
{
	current_ship;
}




Player::Player(std::string nick, size_t coins, Ship * ship)
	: nickname(nick),
	money(coins),
	current_ship(ship)
{

}

Player::Player(std::string nick, size_t coins)
	: nickname(nick),
	money(coins),
	current_ship(nullptr)
{

}

Player::Player(Spaceship * ship)
	: _ship(ship)
{
}

sf::Vector2f Player::getPositionScreen()
{
	return _ship->getPosition();
}

b2Vec2 Player::getPositionWorld()
{
	return _ship->getBody()->GetPosition();
}

float Player::getAngle()
{
	return _ship->getBody()->GetAngle();
}


sf::Shape * Player::getShape()
{
	return _ship->getShape();
}

void Player::setCurrentShip(Ship * ship)
{
	if (current_ship)
		delete current_ship;

	current_ship = ship;
}

void Player::setGameShip(Spaceship * spaceship)
{
	_ship = spaceship;
}





