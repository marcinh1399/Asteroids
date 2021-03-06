#pragma once
#include <cmath>

class TimeManager
{

private:

	float const_cooldown;
	float cooldown;
	float time_after_last_use;

public:

	TimeManager(const float & waiting_time, bool ready_to_use);

	TimeManager & operator+=(const float & delta);

	TimeManager & operator*=(const float & multiplier);

	TimeManager & operator=(const TimeManager & manager);

	bool use();

	bool isReady();

	float getPercentageValue();

	~TimeManager();
};

