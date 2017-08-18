#pragma once
#include "Object.h"
#include "WeaponManager.h"
#include "Spaceship.h"
#include <list>
#include "IListener.h"
#include "KeyboardHandling.h"
#include <memory>
#include <algorithm>
#include "Statistics.h"
#include <string>
#include "Ship.h"


class WeaponManager;

class Player
{

private:

	std::string nickname;
	size_t money;
	Ship * current_ship;


	const int max_lives{ 3 };
	const int initial_lives{ 1 };
	int amount_of_lives;
	Spaceship * _ship;


public:

	Player(std::string nick, size_t coins, Ship * ship);

	Player(std::string nick, size_t coins);

	Player(Spaceship * ship);


	sf::Vector2f getPositionScreen();

	b2Vec2 getPositionWorld();

	float getAngle();

	sf::Shape * getShape();

	void setCurrentShip(Ship * ship);

	void setGameShip(Spaceship * spaceship);

	~Player();

};

