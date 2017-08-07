#include "stdafx.h"
#include "Statistics.h"


Statistics::Statistics()
{
	this->hp = 0;
	this->speed = 0 ;
	this->radians_per_second = 0;
	this->armor = 0;
	this->damage_of_bullets = 0;
	this->bullet_cooldown = 0;
}

Statistics::Statistics(float hp, float speed, float radians_per_second, float armor, float damage_of_bullets, float bullet_cooldown)
{
	this->hp = hp;
	this->speed = speed;
	this->radians_per_second = radians_per_second;
	this->armor = armor;
	this->damage_of_bullets = damage_of_bullets;
	this->bullet_cooldown = bullet_cooldown;
}

Statistics & Statistics::operator=(const Statistics & stats)
{
	this->hp = stats.hp;
	this->speed = stats.speed;
	this->radians_per_second = stats.radians_per_second;
	this->armor = stats.armor;
	this->damage_of_bullets = stats.damage_of_bullets;
	this->bullet_cooldown = stats.bullet_cooldown;

	return *this;
}

Statistics & Statistics::operator+(const Statistics & stats)
{
	this->hp += stats.hp;
	this->speed += stats.speed;
	this->radians_per_second += stats.radians_per_second;
	this->armor += stats.armor;
	this->damage_of_bullets += stats.damage_of_bullets;
	this->bullet_cooldown += stats.bullet_cooldown;

	return *this;
}

Statistics & Statistics::operator-(const Statistics & stats)
{
	this->hp -= stats.hp;
	this->speed -= stats.speed;
	this->radians_per_second -= stats.radians_per_second;
	this->armor -= stats.armor;
	this->damage_of_bullets -= stats.damage_of_bullets;
	this->bullet_cooldown -= stats.bullet_cooldown;

	return *this;
}

Statistics & Statistics::operator*(const float & multiplier)
{
	this->hp *= multiplier;
	this->speed *= multiplier;
	this->radians_per_second *= multiplier;
	this->armor *= multiplier;
	this->damage_of_bullets *= multiplier;
	this->bullet_cooldown *= multiplier;

	return *this;
}

Statistics & Statistics::operator/(const float & divider)
{
	this->hp /= divider;
	this->speed /= divider;
	this->radians_per_second /= divider;
	this->armor /= divider;
	this->damage_of_bullets /= divider;
	this->bullet_cooldown /= divider;

	return *this;
}


