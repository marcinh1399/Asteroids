#pragma once
#include <utility>
#include "Bullet.h"
#include "TimeManager.h"
#include <vector>



class WeaponManager
{

private:

	typedef std::vector<Bullet *>::iterator Iterator;


	std::vector<Bullet *> bullets;
	TimeManager * _time_manager;
	unsigned int quantity;
	const unsigned int max_quantity;

	

public:
	WeaponManager(const unsigned int & max_bullets, unsigned int how_much_bullets, float cooldown);

	std::vector<Bullet *> & getBullets();

	Iterator & bulletAfterImpact(Iterator & iter, const float & dmg);

	Iterator & bulletOutOfMap(Iterator & iter);

	float percentageValueOfCooldown();

	bool isReadyToFire();

	void fire(Bullet * bullet); /// only if isReadyToFire is true

	bool cooldown(); // to get answer why is not ready to fire

	bool lackOfBullets(); // to get answer why is not ready to fire

	void update(const float & delta);

	void addAmountOfBullets(const int & amount);

	void deleteBullets();


	~WeaponManager();
};

