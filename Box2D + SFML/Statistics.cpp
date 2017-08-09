#include "stdafx.h"
#include "Statistics.h"


Statistics::Statistics()
{
	this->hp = 0;
	this->speed = 0 ;
	this->radians_p_s = 0;
	this->armor = 0;
	this->bullet_dmg = 0;
	this->bullet_cdwn = 0;
}

Statistics::Statistics(float hp, float speed, float radians_per_second, float armor, float damage_of_bullets, float bullet_cooldown)
{
	this->hp = hp;
	this->speed = speed;
	this->radians_p_s = radians_per_second;
	this->armor = armor;
	this->bullet_dmg = damage_of_bullets;
	this->bullet_cdwn = bullet_cooldown;
}

Statistics & Statistics::operator=(const Statistics & stats)
{
	this->hp = stats.hp;
	this->speed = stats.speed;
	this->radians_p_s = stats.radians_p_s;
	this->armor = stats.armor;
	this->bullet_dmg = stats.bullet_dmg;
	this->bullet_cdwn = stats.bullet_cdwn;

	return *this;
}

Statistics & Statistics::operator+=(const Statistics & stats)
{
	this->hp += stats.hp;
	this->speed += stats.speed;
	this->radians_p_s += stats.radians_p_s;
	this->armor += stats.armor;
	this->bullet_dmg += stats.bullet_dmg;
	this->bullet_cdwn += stats.bullet_cdwn;

	return *this;
}

Statistics & Statistics::operator-=(const Statistics & stats)
{
	this->hp -= stats.hp;
	this->speed -= stats.speed;
	this->radians_p_s -= stats.radians_p_s;
	this->armor -= stats.armor;
	this->bullet_dmg -= stats.bullet_dmg;
	this->bullet_cdwn -= stats.bullet_cdwn;

	return *this;
}

Statistics & Statistics::operator*=(const float & multiplier)
{
	this->hp *= multiplier;
	this->speed *= multiplier;
	this->radians_p_s *= multiplier;
	this->armor *= multiplier;
	this->bullet_dmg *= multiplier;
	this->bullet_cdwn *= multiplier;

	return *this;
}

Statistics & Statistics::operator*=(const Statistics & stats)
{
	this->hp *= stats.hp;
	this->speed *= stats.speed;
	this->radians_p_s *= stats.radians_p_s;
	this->armor *= stats.armor;
	this->bullet_dmg *= stats.bullet_dmg;
	this->bullet_cdwn *= stats.bullet_cdwn;

	return *this;
}

Statistics & Statistics::operator/=(const float & divider)
{
	this->hp /= divider;
	this->speed /= divider;
	this->radians_p_s /= divider;
	this->armor /= divider;
	this->bullet_dmg /= divider;
	this->bullet_cdwn /= divider;

	return *this;
}

void Statistics::fill()
{
	hp = hp == 0.f ? 1.f : hp;
	speed = speed == 0.f ? 1.f : speed;
	radians_p_s = radians_p_s == 0.f ? 1.f : radians_p_s;
	armor = armor == 0.f ? 1.f : armor;
	bullet_dmg = bullet_dmg == 0.f ? 1.f : bullet_dmg;
	bullet_cdwn = bullet_cdwn == 0.f ? 1.f : bullet_cdwn;
}

void Statistics::reset()
{
	hp = 0;
	speed = 0;
	radians_p_s = 0;
	armor = 0;
	bullet_dmg = 0;
	bullet_cdwn = 0;
}


