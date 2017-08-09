#include "stdafx.h"
#include "Player.h"


void Player::weaponManagers()
{
	_bullet_manager  = std::make_unique<WeaponManager>(500, 200, 0.25f);
	_rocket_manager = std::make_unique<WeaponManager>(50, 0, 5.f);
	_obstacle_manager = std::make_unique<WeaponManager>(5, 0, 60.f);
}

Player::~Player()
{

}

void Player::handling(const float & delta)
{
	auto _b = _ship->getBody();
	float turn = 0.f;
	float move = 0.f;

	for (auto key : pressed_keys)
	{
		switch (key)
		{
			case sf::Keyboard::Key::A: turn -= 1; break;
			case sf::Keyboard::Key::D: turn += 1; break;
			case sf::Keyboard::Key::W: move += 1; break;
			case sf::Keyboard::Key::S: move -= 1; break;
		}
	}

	speed(delta, move);
	angularSpeed(delta, turn);
}

void Player::speed(const float & delta, int move)
{
	float max_speed = _ship->getCurrentStats().speed;
	b2Body * _b = _ship->getBody();
	float current_speed = _b->GetLinearVelocity().Length();
	float acceleration = max_speed / 2.f;

	float alpha = _b->GetAngle();

	b2Vec2 vel{ _b->GetLinearVelocity() };
	float s = move * delta * acceleration;
	vel.x += sin(alpha) * s;
	vel.y -= cos(alpha) * s;

	if (vel.Length() > max_speed)
	{
		vel *= (max_speed / vel.Length());
	}

	_b->SetLinearVelocity(vel);
}

void Player::angularSpeed(const float & delta, int turn)
{
	float max_angular_speed = _ship->getCurrentStats().radians_p_s;
	b2Body * _b = _ship->getBody();
	float current_speed = _b->GetAngularVelocity();
	float acceleration = max_angular_speed / 1.5f;
	
	current_speed += acceleration * turn * delta;

	if (current_speed > max_angular_speed)
	{
		current_speed = max_angular_speed;
	}

	_b->SetAngularVelocity(current_speed);
}


Player::Player(Spaceship * ship, std::shared_ptr<KeyboardHandling> keyboard_handling)
	: IListener(keyboard_handling),
	_ship(ship)
{
	ship_stats = ship->getCurrentStats();
	weaponManagers();
	
	keys.push_back(sf::Keyboard::Key::W);
	keys.push_back(sf::Keyboard::Key::A);
	keys.push_back(sf::Keyboard::Key::S);
	keys.push_back(sf::Keyboard::Key::D);


}

void Player::act(const float & delta)
{
	_ship->act(delta);
}

sf::Vector2f Player::getPositionScreen()
{
	return _ship->getPosition();
}

b2Vec2 Player::getPositionWorld()
{
	return _ship->getBody()->GetPosition();
}

float Player::getAngle()
{
	return _ship->getBody()->GetAngle();
}


sf::Shape * Player::getShape()
{
	return _ship->getShape();
}


bool Player::shoot(Bullet::Type type)
{
	bool fire = false;

	switch (type)
	{
		case Bullet::Type::bullet:		fire = _bullet_manager->fire();		break;
		case Bullet::Type::rocket:		fire = _rocket_manager->fire();		break;
		case Bullet::Type::obstacle:	fire = _obstacle_manager->fire();	break;
	}

	return fire;
}



