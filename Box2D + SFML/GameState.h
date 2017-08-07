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
	std::vector<std::unique_ptr<Object>> objects;
	std::vector< std::unique_ptr<Animation> > expl_animations;


public:

	GameState(std::unique_ptr<StateManager> & u_manager, 
		std::unique_ptr<sf::RenderWindow> & u_window, int width, int height,
		std::shared_ptr<KeyboardHandling> keyboard);
	
	virtual void show() override;

	virtual void update(const float & delta) override;

	virtual void mouseHandle(const sf::Vector2i & v, const bool & clicked) override;

	virtual bool isLoaded() override;
	
	~GameState();
};
