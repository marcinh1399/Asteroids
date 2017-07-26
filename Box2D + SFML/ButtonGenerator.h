#pragma once
#include <string>
#include <fstream>
#include "ButtonBuilder.h"
#include "PressButton.h"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"


class ButtonGenerator
{
	struct ButtonDescription 
	{
		std::string name;
		std::string texture_path;
		std::string sound_path;
		sf::Vector2f position;
	};

	ButtonBuilder * _builder;

	int screen_width;
	int screen_height;

	const std::string path = "menu_buttons.txt";
	std::ifstream f_buttons;
	int lines_in_set = 6;

	sf::Texture texture;
	sf::Sound * _sound;

	ButtonDescription button_description;

	bool readFromFile(std::string name);

	void jumpToNextSet();

	bool readPaths();

	bool readPosition();




public:
	ButtonGenerator(int scrn_width, int scrn_height);

	PressButton * makeButton(std::string name);

	bool isFileOpen();

	~ButtonGenerator();

};

