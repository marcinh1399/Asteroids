#pragma once
#include <utility>
#include "Bullet.h"
#include "TimeManager.h"
#include <vector>
#include <algorithm>
#include "ArmedObject.h"

struct ManagerInit;

class WeaponManager
{

private:


	TimeManager time_manager;
	unsigned int quantity;
	const unsigned int max_quantity;

	

public:
	WeaponManager(const unsigned int & max_bullets, unsigned int how_much_bullets, float cooldown);

	WeaponManager(const ManagerInit & init);

	float percentageValueOfCooldown();

	bool fire();

	void update(const float & delta);

	void updateCooldown(const float & multiplier);

	void addAmountOfBullets(const int & amount);
};

