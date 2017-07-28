#pragma once
#include <string>
#include <fstream>
#include "ButtonBuilder.h"
#include "PressButton.h"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include <iostream>

#define NSOUND


class ButtonGenerator
{
	struct ButtonDescription 
	{
		std::string name;
		std::string texture_path;
		std::string sound_path;
		sf::Vector2f position;

		void show()
		{
			std::cout << "name: " << name << std::endl;
			std::cout << "texture_path: " << texture_path << std::endl;
			std::cout << "sound_path: " << sound_path << std::endl;
			std::cout << "position: (" << position.x << ", " << position.y << ")" << std::endl;
		}
	};

	ButtonBuilder * _builder;

	int screen_width;
	int screen_height;

	const std::string path = "buttons.txt";
	std::ifstream f_buttons;
	int lines_in_set = 6;

	sf::Texture * _texture;
	sf::Sound * _sound;

	ButtonDescription button_description;

	bool readFromFile(std::string name);

	void jumpToNextSet();

	bool readPaths();

	bool readPosition();

	sf::Vector2f getCorrectPosition();




public:
	ButtonGenerator(int scrn_width, int scrn_height);

	PressButton * makeButton(std::string name);

	bool isFileOpen();

	~ButtonGenerator();

};

