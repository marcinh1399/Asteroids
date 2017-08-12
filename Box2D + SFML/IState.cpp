#include "stdafx.h"
#include "IState.h"


IState::IState(std::unique_ptr<StateManager>& u_manager, std::unique_ptr<sf::RenderWindow>& u_window, sf::Vector2f world_bounds, std::shared_ptr<KeyboardHandling> keyboard)
	: _manager(u_manager),
	_window(u_window),
	world_size(world_bounds),
	_keyboard(keyboard)
{
}

IState::~IState()
{
}
