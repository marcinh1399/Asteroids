#pragma once
#include <cmath>

class TimeManager
{

private:

	const float cooldown;
	float time_after_last_use{ INFINITY };
	float percent{ 100.f };

public:
	TimeManager(const int & waiting_time);

	void update(const float & delta);

	bool use();

	bool isReady();

	float getPercentageValue();

	~TimeManager();
};

