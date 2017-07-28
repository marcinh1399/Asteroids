#include "stdafx.h"
#include "IState.h"



IState::IState(std::unique_ptr<StateManager> & u_manager, std::unique_ptr<sf::RenderWindow> & u_window, int width, int height)
	: _manager(u_manager), _window(u_window), screen_width(width), screen_height(height) {}

IState::~IState()
{
}
