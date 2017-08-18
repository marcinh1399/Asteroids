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




Spaceship::Spaceship(b2Body * ptr_body, sf::Shape * ptr_shape, 
	Statistics statistics, std::shared_ptr<KeyboardHandling> keyboard_handling)
	: Object(ptr_body, ptr_shape),
	IListener(keyboard_handling),
	current_stats(statistics)
{
	state = ObjectState::immune;
	_body->SetUserData(this);
	immuneAnimation();
	setKeys();
}

Statistics Spaceship::getCurrentStats()
{
	return current_stats;
}



void Spaceship::act(const float & delta)
{
	handling(delta);

	if (state == ObjectState::immune)
	{
		animationOfReborn(delta);
	}

	updatePosition();
}

void Spaceship::handling(const float & delta)
{
	float turn = 0.f;
	float move = 0.f;

	//////////////////////////////////////////////////////////
	pressed_keys_lock.lock();
	for (auto & pair : keys)
	{
		if (!pair.second)
		{
			continue;
		}

		switch (pair.first)
		{
		case sf::Keyboard::Key::A: turn -= 1; break;
		case sf::Keyboard::Key::D: turn += 1; break;
		case sf::Keyboard::Key::W: move += 1; break;
		case sf::Keyboard::Key::S: move -= 1; break;
		}
	}
	pressed_keys_lock.unlock();
	//////////////////////////////////////////////////////////

	linearVelocity(delta, move);
	angularVelocity(delta, turn);
}

void Spaceship::linearVelocity(const float & delta, int move)
{
	float current_speed = _body->GetLinearVelocity().Length();
	float acceleration = current_stats.speed / 2.f;

	float alpha = _body->GetAngle();

	b2Vec2 vel(_body->GetLinearVelocity());
	float s = move * delta * acceleration;
	vel.x += sin(alpha) * s;
	vel.y -= cos(alpha) * s;

	if (vel.Length() > current_stats.speed)
	{
		vel *= (current_stats.speed / vel.Length());
	}

	_body->SetLinearVelocity(vel);
}


void Spaceship::angularVelocity(const float & delta, int turn)
{
	float current_speed = _body->GetAngularVelocity();
	float acceleration = current_stats.radians_p_s / 1.5f;

	current_speed += acceleration * turn * delta;

	if (current_speed > current_stats.radians_p_s)
	{
		current_speed = current_stats.radians_p_s;
	}

	_body->SetAngularVelocity(current_speed);
}

void Spaceship::immuneAnimation()
{
	_copy_of_shape = _shape;
	sf::ConvexShape * shape = static_cast<sf::ConvexShape *>(_shape);
	sf::Shape * first = new sf::ConvexShape(*shape);
	first->setOutlineColor(sf::Color::Transparent);
	sf::Shape * second = new sf::ConvexShape(*shape);
	std::vector<sf::Shape *> frames;
	frames.push_back(first);
	frames.push_back(second);
	_animation = new Animation(frames, 0.15f, true);
}

void Spaceship::setKeys()
{
	pressed_keys_lock.lock();
	keys.push_back(std::make_pair<sf::Keyboard::Key, bool>(sf::Keyboard::Key::W, false));
	keys.push_back(std::make_pair<sf::Keyboard::Key, bool>(sf::Keyboard::Key::A, false));
	keys.push_back(std::make_pair<sf::Keyboard::Key, bool>(sf::Keyboard::Key::S, false));
	keys.push_back(std::make_pair<sf::Keyboard::Key, bool>(sf::Keyboard::Key::D, false));
	pressed_keys_lock.unlock();
}



Spaceship::~Spaceship()
{
	delete _animation;
}

