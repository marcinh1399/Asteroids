#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "PressButton.h"


class ButtonBuilder
{

private:
	sf::Vector2f position;
	sf::Sprite * _sprite;
	sf::Sound * _sound;


public:
	ButtonBuilder();

	ButtonBuilder * setPosition(sf::Vector2f pos);

	ButtonBuilder * setTexture(sf::Texture * texture);

	ButtonBuilder * setSound(sf::Sound * ptr_sound);

	PressButton * build();

	~ButtonBuilder();
};

