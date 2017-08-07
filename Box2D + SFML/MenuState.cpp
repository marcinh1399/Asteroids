#include "stdafx.h"
#include "MenuState.h"



bool MenuState::loadButtonsFromFile()
{
	bool load{ false };

	if (file_with_names.good() && _generator->isFileOpen())
	{
		load = true;
		std::string name;
		while (!file_with_names.eof())
		{
			file_with_names >> name;
			PressButton * _button = _generator->makeButton(name);
			if (_button != nullptr)
			{
				buttons.push_back(_button);
			}
			else
			{
				load = false;
			}
		}
	}

	return load;
}

MenuState::MenuState(std::unique_ptr<StateManager> & u_manager, 
	std::unique_ptr<sf::RenderWindow> & u_window, int width, int height,
	std::shared_ptr<KeyboardHandling> keyboard)
	: IState(u_manager, u_window, width, height, keyboard)
{
	_generator = new ButtonGenerator(width, height);
	file_with_names.open(path_to_buttons, std::ios::in);
	loaded = loadButtonsFromFile();
}

void MenuState::show()
{
	_window->clear();
	for (auto _button : buttons)
	{
		_window->draw(*(_button->getSprite()));
	}
	_window->display();
}

void MenuState::update(const float & delta)
{
	///////
}

void MenuState::mouseHandle(const sf::Vector2i & v, const bool & pressed)
{
	if (mouse.stateChanged(v, pressed)) // this function update state too
	{
		sf::Vector2f vf(v);
		for (auto _button : buttons)
		{
			_button->cursorOn(vf);
			if (mouse.buttonReleased())
				_button->clicked(vf);
		}
	}
}

bool MenuState::isLoaded()
{
	return loaded;
}

MenuState::~MenuState()
{
	delete _generator;
}
