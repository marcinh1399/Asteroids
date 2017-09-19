#include "stdafx.h"
#include "GameState.h"






GameState::GameState(std::unique_ptr<StateManager>& u_manager,
	std::unique_ptr<sf::RenderWindow>& u_window,
	sf::Vector2f world_bounds, std::shared_ptr<KeyboardHandling> keyboard)
	: IState(u_manager, u_window, world_bounds, keyboard)
{
	world_manager = std::make_unique<WorldManager>(game_objects, keyboard);
	screen_manager = std::make_unique<ScreenManager>(game_objects, u_window);
}

GameState::~GameState()
{
}

void GameState::show()
{
	screen_manager->display();
}

void GameState::update(const float & delta)
{
	world_manager->act(delta);
}

void GameState::mouseHandle(const sf::Vector2i & v, const bool & clicked)
{

}

bool GameState::isLoaded()
{
	return true;
}
