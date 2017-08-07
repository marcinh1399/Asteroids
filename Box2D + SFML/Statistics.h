#pragma once
class Statistics
{

public:

	float hp;
	float speed;
	float radians_per_second;
	float armor;
	float damage_of_bullets;
	float bullet_cooldown;

	Statistics();

	Statistics(float hp, float speed, float radians_per_second,
		float armor, float damage_of_bullets, float bullet_cooldown);

	Statistics & operator=(const Statistics & stats);

	Statistics & operator+(const Statistics & stats);

	Statistics & operator-(const Statistics & stats);

	Statistics & operator*(const float & multiplier);

	Statistics & operator/(const float & multiplier);

};

