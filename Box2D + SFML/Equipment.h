#pragma once
#include "Statistics.h"

class Equipment
{

public:

	enum class Type
	{
		hp = 0,
		engine,
		agility,
		armor,
		bullet,
		gun
	};

private:

	Type type;

	const int max_level{ 10 };
	unsigned int current_level{ 0 };

	const float multiplier_per_level{ 1.2f };
	const float multiplier_cooldown{ 0.9f };

public:

	Equipment(Type type);

	Statistics stats{ 0.f, 0.f, 0.f, 0.f, 0.f, 0.f };

	int getLevel();

	int getMaxLevel();

	void nextLevel();

};

