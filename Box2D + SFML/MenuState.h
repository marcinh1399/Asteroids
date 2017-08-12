#pragma once
#include "IState.h"
#include "PressButton.h"
#include <memory>
#include "SFML\Graphics.hpp"
#include <vector>
#include <string>
#include <fstream>
#include "MouseHandling.h"
#include "FactoryButton.h"
#include "GameState.h"

class MenuState :
	public IState
{
private :

	FactoryButton button_factory;
	std::vector<std::shared_ptr<PressButton>> buttons;

	MouseHandling mouse;


public:
	MenuState(std::unique_ptr<StateManager> & u_manager, 
		std::unique_ptr<sf::RenderWindow> & u_window, sf::Vector2f world_bounds,
		std::shared_ptr<KeyboardHandling> keyboard);

	virtual void show() override;

	virtual void update(const float & delta) override;

	virtual void mouseHandle(const sf::Vector2i & v, const bool & pressed) override;

	virtual bool isLoaded() override;

	~MenuState();
};

