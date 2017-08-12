#include "stdafx.h"
#include "BulletHandling.h"




BulletHandling::BulletHandling(std::shared_ptr<GameObjects> g_objects)
	: IListener(g_objects->keyboard),
	objects(g_objects->objects),
	_factory(g_objects->factory),
	bullet_manager(500, 200, 1.f / 60.f),
	rocket_manager(100, 20, 0.5f),
	obstacle_manager(5, 1, 10.f)
{
	current_manager = &bullet_manager;
	current_type = Bullet::Type::bullet;
	keys.push_back(std::make_pair<sf::Keyboard::Key, bool>(sf::Keyboard::Key::Num1, false));
	keys.push_back(std::make_pair<sf::Keyboard::Key, bool>(sf::Keyboard::Key::Num2, false));
	keys.push_back(std::make_pair<sf::Keyboard::Key, bool>(sf::Keyboard::Key::Num3, false));
	keys.push_back(std::make_pair<sf::Keyboard::Key, bool>(sf::Keyboard::Key::Space, false));
}

BulletHandling::~BulletHandling()
{
}

void BulletHandling::update(const float & delta)
{
	bullet_manager.update(delta);
	rocket_manager.update(delta);
	obstacle_manager.update(delta);

	handling(delta);
}

void BulletHandling::handling(const float & delta)
{
	bool ready_to_fire = false;
	////////////////////////////////////////////////////////////////
	pressed_keys_lock.lock();

	for (auto pair : keys)
	{
		if (!pair.second)
		{
			continue;
		}

		switch (pair.first)
		{
			case sf::Keyboard::Key::Num1:
				current_manager = &bullet_manager;
				current_type = Bullet::Type::bullet;
				break;
			case sf::Keyboard::Key::Num2:
				current_manager = &rocket_manager;
				current_type = Bullet::Type::rocket;
				break;
			case sf::Keyboard::Key::Num3:
				current_manager = &obstacle_manager;
				current_type = Bullet::Type::obstacle;
				break;
			case sf::Keyboard::Key::Space:
				ready_to_fire = true;
				break;
		}
	}

	pressed_keys_lock.unlock();
	////////////////////////////////////////////////////////////////

	if (ready_to_fire)
	{
		bool fire = current_manager->fire();

		if (fire)
		{
			auto missile = _factory->makeBullet(current_type);
			objects.push_back(std::move(missile));
		}
	}
}
