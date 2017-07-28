#pragma once
#include <memory>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "StateManager.h"


class StateManager;

class IState
{

protected:

	std::unique_ptr<StateManager> & _manager;
	std::unique_ptr<sf::RenderWindow> & _window;
	int screen_width;
	int screen_height;

public:
	IState(std::unique_ptr<StateManager> & u_manager, std::unique_ptr<sf::RenderWindow> & u_window, int width, int height);

	virtual void show() = 0;

	virtual void update(const float & delta) = 0;

	virtual void mouseHandle(const sf::Vector2i & v, const bool & clicked) = 0;

	virtual bool isLoaded() = 0;

	~IState();
};

