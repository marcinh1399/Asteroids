#pragma once
#include <cmath>

class TimeManager
{

private:

	const float const_cooldown;
	float cooldown;
	float time_after_last_use;

public:

	TimeManager(const float & waiting_time, bool ready_to_use);

	void update(const float & delta);

	TimeManager & operator+=(const float & delta);

	bool use();

	bool isReady();

	float getPercentageValue();

	void multiplierCooldown(const float & multiplier);

	~TimeManager();
};

