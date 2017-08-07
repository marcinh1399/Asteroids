#include "stdafx.h"
#include "Equipment.h"



void Equipment::makeHP()
{
	type = Type::hp;
}

void Equipment::makeEngine()
{
	type = Type::engine;
}

void Equipment::makeAgility()
{
	type = Type::agility;
}

void Equipment::makeArmor()
{
	type = Type::armor;
}

void Equipment::makeBullet()
{
	type = Type::bullet;
}

void Equipment::makeGun()
{
	type = Type::gun;
}

bool Equipment::nextLevel()
{
	if (current_level == 10)
	{
		return false;
	}
	else
	{
		++current_level;
		return true;
	}
}
