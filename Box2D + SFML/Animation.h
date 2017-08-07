#pragma once
#include "SFML\Graphics.hpp"
#include "AnimationTimeManager.h"
#include <vector>

class Animation
{

private:

	AnimationTimeManager time_manager;
	std::vector<sf::Shape *> v_frames;

	size_t current_frame;
	bool loop;

public:
	Animation(std::vector<sf::Shape *> animation, float time_for_frame, bool loop);

	Animation(sf::Vector2f pos, float radius, float time_for_frame, float frames);

	sf::Shape * getFrame(const float & delta);

	void reset();

	~Animation();
};

