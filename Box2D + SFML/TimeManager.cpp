#include "stdafx.h"
#include "TimeManager.h"




TimeManager::TimeManager(const float & waiting_time, bool ready_to_use)
	: cooldown{ waiting_time }, const_cooldown{ waiting_time }
{
	if (ready_to_use)
	{
		time_after_last_use = INFINITY;
	}
	else
	{
		time_after_last_use = 0;
	}
}


TimeManager & TimeManager::operator+=(const float & delta)
{
	time_after_last_use += delta;
	
	return *this;
}

TimeManager & TimeManager::operator*=(const float & multiplier)
{
	cooldown = const_cooldown * multiplier;

	return *this;
}

bool TimeManager::use()
{
	bool ready = time_after_last_use >= cooldown;

	if (ready)
	{
		time_after_last_use = 0.f;
	}

	return ready;
}

bool TimeManager::isReady()
{
	return time_after_last_use > cooldown;
}

float TimeManager::getPercentageValue()
{
	return (time_after_last_use >= cooldown) ? 100.f : (time_after_last_use / cooldown);
}


TimeManager::~TimeManager()
{
}
