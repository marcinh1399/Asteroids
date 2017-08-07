#pragma once
class AnimationTimeManager
{

private:
	const float duration_of_frame;
	float time;

public:
	AnimationTimeManager(const float & duration);

	AnimationTimeManager & operator+=(const float & delta);

	void reset();

	size_t skipFrames();

};

