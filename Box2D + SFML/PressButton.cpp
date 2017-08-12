#include "stdafx.h"
#include "PressButton.h"


PressButton::PressButton(MenuType type, const sf::Vector2f & pos, sf::Sprite * ptr_sprite, sf::Sound * ptr_sound)
	: position(pos), _sprite(ptr_sprite), _sound(ptr_sound)
{
	this->type = type;
	top_left_corner_pos = Coords::centerInPoint(position, _sprite->getTexture(), sf::Vector2f(1.f, 1.f));
	_sprite->setPosition(top_left_corner_pos);
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
		_sprite->setPosition(Coords::centerInPoint(position, _sprite->getTexture(), scale_if_cursor_on));
	}
	else
	{
		_sprite->setScale(1.f, 1.f);
		_sprite->setPosition(top_left_corner_pos);
	}
}

sf::Sprite * PressButton::getSprite()
{
	return _sprite;
}

PressButton::MenuType PressButton::getType()
{
	return type;
}

PressButton::~PressButton()
{
	delete _sound;
	delete _sprite;
}
