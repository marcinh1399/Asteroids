#pragma once
#include <string>
#include "PressButton.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <memory>

class FactoryButton
{

private:

	struct ButtonDescription
	{
		PressButton::MenuType type;
		std::string texture_path;
		std::string sound_path;
		sf::Vector2f position;
	};

	int menu_width;
	int menu_height;

	const std::string menu_button_sound = "menu_button_sound.wav";


	ButtonDescription play_button{ PressButton::MenuType::play, "play_button.png", 
		menu_button_sound, sf::Vector2f(menu_width / 2, 1 * menu_height / 4) };

	ButtonDescription options_button{ PressButton::MenuType::options, "options_button.png", 
		menu_button_sound, sf::Vector2f(menu_width / 2, menu_height / 2) };

	ButtonDescription exit_button{ PressButton::MenuType::exit, "exit_button.png", 
		menu_button_sound, sf::Vector2f(menu_width / 2, 3 * menu_height / 4) };

public:
	FactoryButton(sf::Vector2f world_bounds);

	std::shared_ptr<PressButton> makeMenuButton(PressButton::MenuType type);

	~FactoryButton();
};

