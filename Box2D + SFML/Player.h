#pragma once
#include "Object.h"
#include "WeaponManager.h"
#include "Spaceship.h"
#include <list>
#include "IListener.h"
#include "KeyboardHandling.h"
#include <memory>
#include <algorithm>


class WeaponManager;

class Player
	: IListener
{

private:

	TimeManager immune_time{ 5.f, false };
	TimeManager transp_time{ 0.15f, false };

	const int max_lives{ 3 };
	const int initial_lives{ 1 };
	int amount_of_lives;

	WeaponManager * _bullet_manager;
	WeaponManager * _rocket_manager;
	WeaponManager * _obstacle_manager;

	Spaceship * _ship;

	void weaponManagers();

	// Inherited via IListener
	virtual void handling() override;


public:
	Player(Spaceship * ptr_ship, std::shared_ptr<KeyboardHandling> keyboard_handling);

	void act(const float & delta);

	sf::Vector2f getPositionScreen();

	b2Vec2 getPositionWorld();

	float getAngle();

	Spaceship * getShip();

	sf::Shape * getShape();

	~Player();

};

