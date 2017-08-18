#include "stdafx.h"
#include "CreatingPlayerState.h"




void CreatingPlayerState::loadShips()
{
	for (int i = 0; i < static_cast<int>(SpaceshipTypes::ShipType::none); ++i)
	{
		ships_to_choose.push_back(spaceship_types->getType(static_cast<SpaceshipTypes::ShipType>(i)));
	}
}

void CreatingPlayerState::setKeys()
{
	pressed_keys_lock.lock();
	for (int i = 0; i <= static_cast<int>(sf::Keyboard::Key::Num9); ++i)
	{
		keys.push_back(std::make_pair<sf::Keyboard::Key, bool>(static_cast<sf::Keyboard::Key>(i), false));
	}
	keys.push_back(std::make_pair<sf::Keyboard::Key, bool>(sf::Keyboard::Key::Left, false));
	keys.push_back(std::make_pair<sf::Keyboard::Key, bool>(sf::Keyboard::Key::Right, false));
	keys.push_back(std::make_pair<sf::Keyboard::Key, bool>(sf::Keyboard::Key::Return, false));
	pressed_keys_lock.unlock();
}

void CreatingPlayerState::typingNickname()
{
	sf::String s = "";

	pressed_keys_lock.lock();

/*
	
	for (auto pair : keys)
	{
		if (!pair.second)
			continue;

		switch (pair.first)
		{
		
		default: s += pair.first;	break;
		}
	}

	*/
	pressed_keys_lock.unlock();
}

void CreatingPlayerState::choosingShip()
{
}

CreatingPlayerState::CreatingPlayerState(std::unique_ptr<StateManager>& u_manager,
	std::unique_ptr<sf::RenderWindow>& u_window, sf::Vector2f world_bounds, 
	std::shared_ptr<KeyboardHandling> keyboard)
	: IState(u_manager, u_window, world_bounds, keyboard),
	IListener(keyboard)
{
	spaceship_types = SpaceshipTypes::getInstance();
	loadShips();
	setKeys();
}

CreatingPlayerState::~CreatingPlayerState()
{
}

void CreatingPlayerState::show()
{
}

void CreatingPlayerState::update(const float & delta)
{
}

void CreatingPlayerState::mouseHandle(const sf::Vector2i & v, const bool & clicked)
{
}

bool CreatingPlayerState::isLoaded()
{
	return false;
}

void CreatingPlayerState::handling(const float & delta)
{
	
}
