#include "stdafx.h"
#include "WeaponManager.h"

typedef std::vector<Bullet *>::iterator Iterator;

WeaponManager::WeaponManager(const unsigned int & max_bullets, 
				unsigned int how_much_bullets, float cooldown)
	: max_quantity(max_bullets), 
	quantity(how_much_bullets),
	time_manager(TimeManager(cooldown, true))
{
}

float WeaponManager::percentageValueOfCooldown()
{
	return time_manager.getPercentageValue();
}



bool WeaponManager::fire()
{
	return time_manager.use();
}


void WeaponManager::update(const float & delta)
{
	time_manager += delta;
}

void WeaponManager::updateCooldown(const float & multiplier)
{
	time_manager *= multiplier;
}

void WeaponManager::addAmountOfBullets(const int & amount)
{
	quantity += amount;

	if (quantity > max_quantity)
	{
		quantity = max_quantity;
	}
}
