#include "stdafx.h"
#include "WeaponManager.h"

typedef std::vector<Bullet *>::iterator Iterator;

WeaponManager::WeaponManager(const unsigned int & max_bullets, 
				unsigned int how_much_bullets, float cooldown)
	: max_quantity{ max_bullets }, 
	quantity{ how_much_bullets },
	_time_manager{ new TimeManager(cooldown, true)}
{
}

std::vector<Bullet *> & WeaponManager::getBullets()
{
	return bullets;
}

Iterator & WeaponManager::bulletAfterImpact(Iterator & iter, const float & dmg)
{
	(*iter)->hit(dmg);
	return iter;
}


Iterator & WeaponManager::bulletOutOfMap(Iterator & iter)
{
	return bullets.erase(iter);
}

float WeaponManager::percentageValueOfCooldown()
{
	return _time_manager->getPercentageValue();
}

bool WeaponManager::isReadyToFire()
{
	return _time_manager->isReady() && quantity != 0;
}

void WeaponManager::fire(Bullet * _bullet)
{
	if (_time_manager->use())
	{
		bullets.push_back(_bullet);
	}
	else
	{
		delete _bullet;
	}
}

bool WeaponManager::cooldown()
{
	return !_time_manager->isReady();
}

bool WeaponManager::lackOfBullets()
{
	return quantity == 0;
}

void WeaponManager::update(const float & delta)
{
	(*_time_manager) += delta;
}

void WeaponManager::addAmountOfBullets(const int & amount)
{
	quantity += amount;

	if (quantity > max_quantity)
	{
		quantity = max_quantity;
	}
}

void WeaponManager::deleteBullets()
{
	
}


WeaponManager::~WeaponManager()
{
	for (auto * ptr : bullets)
	{
		delete ptr;
	}

	bullets.clear();
}
