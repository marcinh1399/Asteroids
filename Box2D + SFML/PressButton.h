#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "Coords.h"

class PressButton
{

public:

	enum class MenuType
	{
		play,
		options,
		exit
	};
private:

	sf::Vector2f position;
	sf::Vector2f top_left_corner_pos;
	sf::Sprite * _sprite;
	sf::Sound * _sound;

	MenuType type;

	const sf::Vector2f scale_if_cursor_on{ 1.1f, 1.1f };


public:

	PressButton(MenuType type, const sf::Vector2f & pos, sf::Sprite * ptr_sprite, sf::Sound * ptr_sound);

	bool clicked(sf::Vector2f v);

	void cursorOn(sf::Vector2f v);

	sf::Sprite * getSprite();

	PressButton::MenuType getType();

	~PressButton();
};

