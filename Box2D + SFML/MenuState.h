#pragma once
#include "IState.h"
#include "PressButton.h"
#include "ButtonGenerator.h"
#include <memory>
#include "SFML\Graphics.hpp"
#include <vector>
#include <string>
#include <fstream>
#include "MouseHandling.h"

class MenuState :
	public IState
{
private :

	std::vector<PressButton *> buttons;
	ButtonGenerator * _generator;
	

	const std::string path_to_buttons = "menu_buttons.txt";
	std::ifstream file_with_names;
	bool loaded;

	MouseHandling mouse;

	bool loadButtonsFromFile();


public:
	MenuState(std::unique_ptr<StateManager> & u_manager, std::unique_ptr<sf::RenderWindow> & u_window, int width, int height);

	virtual void show() override;

	virtual void update(const float & delta) override;

	virtual void mouseHandle(const sf::Vector2i & v, const bool & pressed) override;

	virtual bool isLoaded() override;

	~MenuState();
};

