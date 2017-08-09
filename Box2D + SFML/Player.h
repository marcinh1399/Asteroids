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

	std::unique_ptr<WeaponManager> _bullet_manager;
	std::unique_ptr<WeaponManager> _rocket_manager;
	std::unique_ptr<WeaponManager> _obstacle_manager;

	Spaceship * _ship;

	Statistics ship_stats;

	void weaponManagers();

	// Inherited via IListener
	virtual void handling(const float & delta) override;

	void speed(const float & delta, int move);

	void angularSpeed(const float & delta, int turn);


public:
	Player(Spaceship * ship, std::shared_ptr<KeyboardHandling> keyboard_handling);

	void act(const float & delta);

	sf::Vector2f getPositionScreen();

	b2Vec2 getPositionWorld();

	float getAngle();

	sf::Shape * getShape();

	bool shoot(Bullet::Type type);

	~Player();

};

