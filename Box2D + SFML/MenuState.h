#pragma once
#include "IState.h"
#include <memory>
#include "SFML\Graphics.hpp"

class MenuState :
	public IState
{
public:
	MenuState(std::unique_ptr<StateManager> & u_manager, std::unique_ptr<sf::RenderWindow> & u_window);

	virtual void show() override;

	virtual void update() override;

	~MenuState();
};

