#include "stdafx.h"
#include "MenuState.h"




MenuState::MenuState(std::unique_ptr<StateManager> & u_manager, std::unique_ptr<sf::RenderWindow> & u_window)
	: IState(u_manager, u_window)
{
}

void MenuState::show()
{
}

void MenuState::update()
{
}

MenuState::~MenuState()
{
}
