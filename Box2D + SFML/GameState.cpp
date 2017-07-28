#include "stdafx.h"
#include "GameState.h"




GameState::GameState(std::unique_ptr<StateManager>& u_manager, std::unique_ptr<sf::RenderWindow>& u_window, int width, int height)
	: IState(u_manager, u_window, width, height)
{
	_world_manager = std::make_unique<WorldManager>(width, height, objects);
	_screen_manager = std::make_unique<ScreenManager>(objects, _window);
}

GameState::~GameState()
{
}

void GameState::show()
{
	_screen_manager->display();
}

void GameState::update(const float & delta)
{
	_world_manager->act(delta);
}

void GameState::mouseHandle(const sf::Vector2i & v, const bool & clicked)
{

}

bool GameState::isLoaded()
{
	return true;
}
