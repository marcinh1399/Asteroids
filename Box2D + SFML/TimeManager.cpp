#include "stdafx.h"
#include "TimeManager.h"




TimeManager::TimeManager(const int & waiting_time)
	: cooldown(waiting_time) {}

void TimeManager::update(const float & delta)
{
	time_after_last_use += delta;

	if (time_after_last_use >= cooldown)
	{
		percent = 100.f;
	}
	else
	{
		percent = time_after_last_use * 100.f / cooldown;
	}
}

bool TimeManager::use()
{
	bool ready = time_after_last_use > cooldown;

	if (ready)
	{
		time_after_last_use = 0.f;
		percent = 0.f;
	}

	return ready;
}

bool TimeManager::isReady()
{
	return time_after_last_use > cooldown;
}

float TimeManager::getPercentageValue()
{
	return percent;
}

TimeManager::~TimeManager()
{
}
