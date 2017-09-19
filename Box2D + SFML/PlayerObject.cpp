#include "stdafx.h"
#include "PlayerObject.h"



void PlayerObject::move(const float & delta, int move, int turn)
{
	float angle = _body->GetAngle() + turn * stats.radians_p_s * delta;

	float acceleration = stats.speed / 2.f;

	auto linear_velocity = _body->GetLinearVelocity();

	float current_speed = linear_velocity.Length();

	float speed = move * acceleration * delta;

	linear_velocity.x += sinf(angle) * speed;
	linear_velocity.y -= cosf(angle) * speed;

	if (linear_velocity.Length() > stats.speed)
		linear_velocity *= (stats.speed / linear_velocity.Length());


	_body->SetTransform(_body->GetPosition(), angle);
	_body->SetLinearVelocity(linear_velocity);
}


PlayerObject::PlayerObject(b2Body * body, sf::Shape * shape, Statistics statistics, std::shared_ptr<KeyboardHandling> keyboard)
	: ArmedObject(body, shape, statistics),
	IListener(keyboard)
{
	pushKey(sf::Keyboard::Key::W);
	pushKey(sf::Keyboard::Key::A);
	pushKey(sf::Keyboard::Key::S);
	pushKey(sf::Keyboard::Key::D);

	pushKey(sf::Keyboard::Key::Num1);
	pushKey(sf::Keyboard::Key::Num2);
	pushKey(sf::Keyboard::Key::Num3);

	pushKey(sf::Keyboard::Key::Space);
}


PlayerObject::~PlayerObject()
{
}


void PlayerObject::handling(const float & delta)
{
	int move = 0;
	int turn = 0;

	pressed_keys_lock.lock();

	for (auto & pair : keys)
	{
		if (!pair.second)
			continue;

		switch (pair.first)
		{
		case sf::Keyboard::Key::A: turn -= 1; break;
		case sf::Keyboard::Key::D: turn += 1; break;
		case sf::Keyboard::Key::W: move += 1; break;
		case sf::Keyboard::Key::S: move -= 1; break;

		case sf::Keyboard::Key::Num1: setManager(Bullet::Type::bullet);		break;
		case sf::Keyboard::Key::Num2: setManager(Bullet::Type::rocket);		break;
		case sf::Keyboard::Key::Num3: setManager(Bullet::Type::obstacle);	break;

		case sf::Keyboard::Key::Space: fire();	break;
		}
	}

	pressed_keys_lock.unlock();

	this->move(delta, move, turn);
}


void PlayerObject::act(const float & delta)
{
	updateMissileManager(delta);

	handling(delta);

	updatePosition();
}
