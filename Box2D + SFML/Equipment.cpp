#include "stdafx.h"
#include "Equipment.h"


Equipment::Equipment(Type type)
{
	this->type = type;
	this->current_level = 0;

	switch (type)
	{
		case Equipment::Type::hp:		stats.hp = 1.f;				break;
		case Equipment::Type::engine:	stats.speed = 1.f;			break;
		case Equipment::Type::agility:	stats.radians_p_s = 1.f;	break;
		case Equipment::Type::armor:	stats.armor = 1.f;			break;
		case Equipment::Type::bullet:	stats.bullet_dmg = 1.f;		break;
		case Equipment::Type::gun:		stats.bullet_cdwn = 1.f;	break;
	}
}

int Equipment::getLevel()
{
	return current_level;
}

int Equipment::getMaxLevel()
{
	return max_level;
}


void Equipment::nextLevel()
{
	++current_level;

	switch (type)
	{
		case Type::hp:		stats.hp *= multiplier_per_level;			break;
		case Type::engine:	stats.speed	*= multiplier_per_level;		break;
		case Type::agility:	stats.radians_p_s *= multiplier_per_level;	break;
		case Type::armor:	stats.armor *= multiplier_per_level;		break;
		case Type::bullet:	stats.bullet_dmg *= multiplier_per_level;	break;
		case Type::gun:		stats.bullet_cdwn *= multiplier_cooldown;	break;
	}
}
