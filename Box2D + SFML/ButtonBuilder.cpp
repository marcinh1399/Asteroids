#include "stdafx.h"
#include "ButtonBuilder.h"


ButtonBuilder::ButtonBuilder()
{
}

ButtonBuilder * ButtonBuilder::setPosition(sf::Vector2f pos)
{
	position = pos;
	return this;
}

ButtonBuilder * ButtonBuilder::setTexture(sf::Texture * texture)
{
	_sprite = new sf::Sprite();
	_sprite->setTexture(*texture);

	return this;
}

ButtonBuilder * ButtonBuilder::setSound(sf::Sound * ptr_sound)
{
	_sound = ptr_sound;

	return this;
}



PressButton * ButtonBuilder::build()
{
	_sprite->setPosition(position);
	return new PressButton(position, _sprite, _sound);
}


ButtonBuilder::~ButtonBuilder()
{
}

