#include "stdafx.h"
#include "PressButton.h"


PressButton::PressButton(const sf::Vector2f & pos, sf::Sprite * ptr_sprite, sf::Sound * ptr_sound)
	: position(pos), _sprite(ptr_sprite), _sound(ptr_sound)
{
}


bool PressButton::clicked(sf::Vector2f v)
{
	bool hit = _sprite->getGlobalBounds().contains(v);

	if (hit)
	{
		_sound->play();
	}

	return hit;
}

PressButton::~PressButton()
{
	delete _sound;
	delete _sprite;
}
