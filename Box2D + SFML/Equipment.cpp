#include "stdafx.h"
#include "Equipment.h"


Equipment::Equipment()
{
}


Equipment::~Equipment()
{
}

void Equipment::makeHP(const unsigned int & level)
{
	if (level <= max_level)
	{
		current_level = level;
		stats.hp += (level - current_level) * multiplier_per_level;
	}
}

void Equipment::makeEngine(const unsigned int & level)
{
	if (level <= max_level)
	{
		current_level = level;
		stats.speed += (level - current_level) * multiplier_per_level;
	}
}

void Equipment::makeAgility(const unsigned int & level)
{
	if (level <= max_level)
	{
		current_level = level;
		stats.radians_per_second += (level - current_level) * multiplier_per_level;
	}
}

void Equipment::makeArmor(const unsigned int & level)
{
	if (level <= max_level)
	{
		current_level = level;
		stats.armor += (level - current_level) * multiplier_per_level;
	}
}

void Equipment::makeBullet(const unsigned int & level)
{
	if (level <= max_level)
	{
		current_level = level;
		stats.damage_of_bullets += (level - current_level) * multiplier_per_level;
	}
}

void Equipment::makeGun(const unsigned int & level)
{
	if (level <= max_level)
	{
		current_level = level;
		stats.bullet_cooldown -= (level - current_level) * multiplier_per_level;
	}
}
