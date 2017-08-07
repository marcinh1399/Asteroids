#include "stdafx.h"
#include "Animation.h"



Animation::Animation(std::vector<sf::Shape *> animation, float time_for_frame, bool loop)
	: time_manager{ time_for_frame },
	v_frames{ animation }
{
	current_frame = 0;
	this->loop = loop;
}

Animation::Animation(sf::Vector2f pos, float radius, float time_for_frame, float frames)
	: time_manager{ time_for_frame }
{
	current_frame = 0;
	loop = false;

	float multiplier = 1.05f;
	float radius_multiplier = 1.f;

	for (int i = 0; i < frames; ++i)
	{
		sf::CircleShape * _shape = new sf::CircleShape(radius * radius_multiplier);
		_shape->setPosition(pos);
		_shape->setOutlineThickness(10 * radius_multiplier);
		if (i < frames / 2)
		{
			_shape->setFillColor(sf::Color::White);
			_shape->setOutlineColor(sf::Color::Yellow);
		}
		else
		{
			_shape->setFillColor(sf::Color::Yellow);
			_shape->setOutlineColor(sf::Color::Red);
		}

		v_frames.push_back(_shape);

		radius_multiplier *= multiplier;
	}
}

sf::Shape * Animation::getFrame(const float & delta)
{
	time_manager += delta;
	
	current_frame = current_frame + time_manager.skipFrames();

	sf::Shape * frame{ nullptr };

	if (loop)
	{
		current_frame %= v_frames.size();
		frame = v_frames[current_frame];
	}
	else
	{
		if (current_frame < v_frames.size())
		{
			frame = v_frames[current_frame];
		}
	}

	return frame;
}

void Animation::reset()
{
	time_manager.reset();
	current_frame = 0;
}

Animation::~Animation()
{
	for (auto frame : v_frames)
	{
		delete frame;
	}

	v_frames.clear();
}
