#include "stdafx.h"
#include "Player.h"


void Player::weaponManagers()
{
	_bullet_manager = new WeaponManager(500, 200, 0.25f);
	_rocket_manager = new WeaponManager(50, 0, 5.f);
	_obstacle_manager = new WeaponManager(5, 0, 60.f);
}

Player::~Player()
{
	delete _bullet_manager;
	delete _rocket_manager;
	delete _obstacle_manager;
}

void Player::handling()
{
	auto _b = _ship->getBody();
	float turn = 0.f;
	float turn_per_second = 0.2f;
	float move = 0.f;
	float move_per_second = 0.5f;

	for (auto key : pressed_keys)
	{
		switch (key)
		{
		case sf::Keyboard::Key::A: turn -= turn_per_second; break;
		case sf::Keyboard::Key::D: turn += turn_per_second; break;
		case sf::Keyboard::Key::W: move += move_per_second; break;
		case sf::Keyboard::Key::S: move -= move_per_second; break;
		}
	}


	
	turn += _b->GetAngularVelocity();

	_b->SetAngularVelocity(turn);

	float alpha = _b->GetAngle();

	b2Vec2 vel{ _b->GetLinearVelocity() };
	vel.x += sin(alpha) * move;
	vel.y -= cos(alpha) * move;
	
	_b->SetLinearVelocity(vel);
}


Player::Player(Spaceship * ptr_ship, std::shared_ptr<KeyboardHandling> keyboard_handling)
	: _ship{ ptr_ship },
	IListener{ keyboard_handling }
{
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

Spaceship * Player::getShip()
{
	return _ship;
}

sf::Shape * Player::getShape()
{
	return _ship->getShape();
}



