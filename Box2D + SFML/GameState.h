#pragma once
#include "IState.h"
#include "WorldManager.h"
#include "ScreenManager.h"
#include "GameObjects.h"
#include <SFML\Graphics.hpp>



class GameState :
	public IState
{

private:


	std::unique_ptr<WorldManager> world_manager;
	std::unique_ptr<ScreenManager> screen_manager;

	GameObjects game_objects;


public:

	GameState(std::unique_ptr<StateManager> & u_manager,
		std::unique_ptr<sf::RenderWindow> & u_window, sf::Vector2f world_bounds,
		std::shared_ptr<KeyboardHandling> keyboard);
	
	virtual void show() override;

	virtual void update(const float & delta) override;

	virtual void mouseHandle(const sf::Vector2i & v, const bool & clicked) override;

	virtual bool isLoaded() override;
	
	~GameState();
};
