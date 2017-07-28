#include "stdafx.h"
#include "PressButton.h"


PressButton::PressButton(const sf::Vector2f & pos, sf::Sprite * ptr_sprite, sf::Sound * ptr_sound)
	: position(pos), _sprite(ptr_sprite), _sound(ptr_sound)
{
	position = _sprite->getPosition();
}


bool PressButton::clicked(sf::Vector2f v)
{
	bool hit = _sprite->getGlobalBounds().contains(v);

	if (hit)
	{
		//_sound->play();
		printf("clicked\n");
	}

	return hit;
}

void PressButton::cursorOn(sf::Vector2f v)
{
	if (_sprite->getGlobalBounds().contains(v))
	{
		_sprite->setScale(scale_if_cursor_on);
		sf::Vector2f pos = position;
		pos.x -= (scale_if_cursor_on.x - 1) * _sprite->getTexture()->getSize().x / 2;
		pos.y -= (scale_if_cursor_on.y - 1) * _sprite->getTexture()->getSize().y / 2;
		_sprite->setPosition(pos);
	}
	else
	{
		_sprite->setScale(1.f, 1.f);
		_sprite->setPosition(position);
	}
}

sf::Sprite * PressButton::getSprite()
{
	return _sprite;
}

PressButton::~PressButton()
{
	delete _sound;
	delete _sprite;
}
