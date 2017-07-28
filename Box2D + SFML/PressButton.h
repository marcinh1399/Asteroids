#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

class PressButton
{
private:

	sf::Vector2f position;
	sf::Sprite * _sprite;
	sf::Sound * _sound;

	const sf::Vector2f scale_if_cursor_on{ 1.1f, 1.1f };


public:
	PressButton(const sf::Vector2f & pos, sf::Sprite * ptr_sprite, sf::Sound * ptr_sound);

	bool clicked(sf::Vector2f v);

	void cursorOn(sf::Vector2f v);

	sf::Sprite * getSprite();

	~PressButton();
};

