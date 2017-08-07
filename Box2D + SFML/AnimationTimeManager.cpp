#include "stdafx.h"
#include "AnimationTimeManager.h"



AnimationTimeManager::AnimationTimeManager(const float & duration)
	: duration_of_frame{ duration }
{
	time = 0.f;
}

AnimationTimeManager & AnimationTimeManager::operator+=(const float & delta)
{
	time += delta;
	return *this;
}

void AnimationTimeManager::reset()
{
	time = 0.f;
}

size_t AnimationTimeManager::skipFrames()
{
	size_t frames = static_cast<int>(time / duration_of_frame);
	time -= duration_of_frame * frames;

	return frames;
}