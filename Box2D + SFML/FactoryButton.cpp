#include "stdafx.h"
#include "FactoryButton.h"




FactoryButton::FactoryButton(sf::Vector2f world_bounds)
	: menu_width(world_bounds.x), menu_height(world_bounds.y)
{
}

std::shared_ptr<PressButton> FactoryButton::makeMenuButton(PressButton::MenuType type)
{
	ButtonDescription desctiption;

	switch (type)
	{
		case PressButton::MenuType::play:		desctiption = play_button;		break;
		case PressButton::MenuType::options:	desctiption = options_button;	break;
		case PressButton::MenuType::exit:		desctiption = exit_button;		break;
	}

	sf::Texture * texture = new sf::Texture;
	bool texture_loaded = texture->loadFromFile(desctiption.texture_path);
	
	bool sound_loaded = true;
	
	/*
	sf::SoundBuffer buffer;
	sound_loaded = buffer.loadFromFile(desctiption.sound_path);
	*/

	
	if (!(texture_loaded && sound_loaded))
	{
		return std::shared_ptr<PressButton>();
	}

	sf::Sprite * sprite = new sf::Sprite(*texture);
	sf::Sound * sound = nullptr;
		//new sf::Sound(buffer);


	return std::make_shared<PressButton>(desctiption.type, desctiption.position, sprite, sound);
}


FactoryButton::~FactoryButton()
{
}
