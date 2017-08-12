#pragma once
#include <memory>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "StateManager.h"
#include "KeyboardHandling.h"


class StateManager;

class IState
{

protected:

	std::unique_ptr<StateManager> & _manager;
	std::unique_ptr<sf::RenderWindow> & _window;
	std::shared_ptr<KeyboardHandling> _keyboard;

	sf::Vector2f world_size;

public:

	IState(std::unique_ptr<StateManager> & u_manager,
		std::unique_ptr<sf::RenderWindow> & u_window, sf::Vector2f world_bounds,
		std::shared_ptr<KeyboardHandling> keyboard);

	virtual void show() = 0;

	virtual void update(const float & delta) = 0;

	virtual void mouseHandle(const sf::Vector2i & v, const bool & clicked) = 0;

	virtual bool isLoaded() = 0;

	~IState();
};

