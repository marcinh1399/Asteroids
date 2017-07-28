#pragma once
#include "IState.h"
#include "WorldManager.h"
#include "ScreenManager.h"


class GameState :
	public IState
{

private:
	std::unique_ptr<WorldManager> _world_manager;
	std::unique_ptr<ScreenManager> _screen_manager;
	std::vector<Object *> objects;



public:
	GameState(std::unique_ptr<StateManager> & u_manager, std::unique_ptr<sf::RenderWindow> & u_window, int width, int height);
	
	virtual void show() override;

	virtual void update(const float & delta) override;

	virtual void mouseHandle(const sf::Vector2i & v, const bool & clicked) override;

	virtual bool isLoaded() override;
	
	~GameState();
};

