#pragma once
#include "SFML\Graphics.hpp"
#include "StateManager.h"
#include <memory>

class IState
{
	std::unique_ptr<StateManager> & _manager;
	std::unique_ptr<sf::RenderWindow> & _window;

public:
	IState(std::unique_ptr<StateManager> & u_manager, std::unique_ptr<sf::RenderWindow> & u_window)
		: _manager(u_manager), _window(u_window) {}

	virtual void show() = 0;

	virtual void update() = 0;

	~IState();
};

