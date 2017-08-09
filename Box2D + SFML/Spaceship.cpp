#include "stdafx.h"
#include "Spaceship.h"



void Spaceship::animationOfReborn(const float & delta)
{
	immune_time += delta;
	_shape = _animation->getFrame(delta);

	if (immune_time.use())
	{
		_shape = _copy_of_shape;
		state = ObjectState::alive;
	}
}

Statistics Spaceship::getCurrentStats()
{
	return current_stats;
}



void Spaceship::update()
{
	current_stats.reset();
/*
	for (auto eq : equipment)
	{
		current_stats += eq.stats;
	}
	*/

	current_stats.fill();

	current_stats *= basic_stats;
}


Spaceship::Spaceship(float hp, b2Body * ptr_body, sf::Shape * ptr_shape, 
	float dmg, Statistics statistics)
	: Object{ hp, ptr_body, ptr_shape, dmg },
	basic_stats{ statistics },
	current_stats{ statistics }
{
	basic_stats.hp *= hp;

	current_stats_version = 0;
	state = ObjectState::immune;
	_body->SetUserData(this);
	_copy_of_shape = ptr_shape;
	sf::ConvexShape * shape = dynamic_cast<sf::ConvexShape *>(_shape);
	sf::Shape * first = new sf::ConvexShape(*shape);
	first->setOutlineColor(sf::Color::Transparent);
	sf::Shape * second = new sf::ConvexShape(*shape);
	std::vector<sf::Shape *> frames;
	frames.push_back(first);
	frames.push_back(second);
	_animation = new Animation(frames, 0.15f, true);
}

Spaceship::Spaceship(b2Body * ptr_body, sf::Shape * ptr_shape, Statistics statistics)
	: Object(ptr_body, ptr_shape),
	basic_stats(statistics),
	current_stats(statistics)
{
	current_stats_version = 0;
	state = ObjectState::immune;
	_body->SetUserData(this);
	_copy_of_shape = ptr_shape;
	sf::ConvexShape * shape = dynamic_cast<sf::ConvexShape *>(_shape);
	sf::Shape * first = new sf::ConvexShape(*shape);
	first->setOutlineColor(sf::Color::Transparent);
	sf::Shape * second = new sf::ConvexShape(*shape);
	std::vector<sf::Shape *> frames;
	frames.push_back(first);
	frames.push_back(second);
	_animation = new Animation(frames, 0.15f, true);
}



void Spaceship::act(const float & delta)
{
	if (state == ObjectState::immune)
	{
		animationOfReborn(delta);
	}

	updatePosition();
}


Spaceship::~Spaceship()
{
	delete _animation;
}

