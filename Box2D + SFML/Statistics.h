#pragma once
class Statistics
{

public:

	float hp;
	float speed;
	float radians_p_s;
	float armor;
	float bullet_dmg;
	float bullet_cdwn;

	Statistics();

	Statistics(float hp, float speed, float radians_per_second,
		float armor, float damage_of_bullets, float bullet_cooldown);

	Statistics & operator=(const Statistics & stats);

	Statistics & operator+=(const Statistics & stats);

	Statistics & operator-=(const Statistics & stats);

	Statistics & operator*=(const float & multiplier);

	Statistics & operator*=(const Statistics & stats);

	Statistics & operator/=(const float & multiplier);

	void fill();

	void reset();
};

