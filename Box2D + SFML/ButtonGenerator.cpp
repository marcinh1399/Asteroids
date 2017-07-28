#include "stdafx.h"
#include "ButtonGenerator.h"



bool ButtonGenerator::readFromFile(std::string name)
{
	f_buttons.clear();
	f_buttons.seekg(0, std::ios::beg);

	std::string current_name;

	bool found{ false };

	do {
		f_buttons >> current_name;

		if (current_name == name)
		{
			button_description.name = name;
			found = true;
		}
		else
		{
			jumpToNextSet();
		}

	} while (!f_buttons.eof() && !found);

	if (found)
	{
		found = readPaths();
		found = found && readPosition();
	}

	return found;
}

void ButtonGenerator::jumpToNextSet()
{
	std::string empty;

	if (!f_buttons.eof())
	{
		for (int i = 0; i < lines_in_set; i++)
		{
			std::getline(f_buttons, empty);
		}
	}
}

bool ButtonGenerator::readPaths()
{
	bool read{ true };

	f_buttons >> button_description.texture_path
		>> button_description.sound_path;
	
	return read;
}

bool ButtonGenerator::readPosition()
{
	bool read{ true };

	int type = -1;

	f_buttons >> type;

	switch (type)
	{
	case 1:
		f_buttons >> button_description.position.x;
		f_buttons >> button_description.position.y;
		break;
	case 2:
		int nominator, denominator; /// TODO: add validation for this data
		f_buttons >> nominator >> denominator;
		button_description.position.x = nominator * screen_width / denominator;
		f_buttons >> nominator >> denominator;
		button_description.position.y = nominator * screen_height / denominator;
		break;
	default:
		read = false;
		break;
	}

	return read;
}

sf::Vector2f ButtonGenerator::getCorrectPosition()
{
	button_description.position.x -= _texture->getSize().x / 2;
	button_description.position.y -= _texture->getSize().y / 2;
	return button_description.position;
}

ButtonGenerator::ButtonGenerator(int scrn_width, int scrn_height)
	: screen_width(scrn_width), screen_height(scrn_height)
{
	_builder = new ButtonBuilder();
	f_buttons.open(path, std::ios::in);
}

PressButton * ButtonGenerator::makeButton(std::string name)
{
	PressButton * _button{ nullptr };
	_texture = new sf::Texture();
	bool loaded{ true };

	bool read = readFromFile(name);
	button_description.show();

	if (read)
	{	
		loaded = loaded && _texture->loadFromFile(button_description.texture_path);

	#ifndef NSOUND
		sf::SoundBuffer buffer;
		loaded = loaded && buffer.loadFromFile(button_description.sound_path);
		_sound->setBuffer(buffer);
	#endif 

	}
	else
	{
		loaded = false;
	}

	if (loaded)
	{
		_button = _builder
			->setTexture(_texture)
			->setSound(_sound)
			->setPosition(getCorrectPosition())
			->build();
	}

	return _button;
}

bool ButtonGenerator::isFileOpen()
{
	return f_buttons.good();
}

ButtonGenerator::~ButtonGenerator()
{
}
