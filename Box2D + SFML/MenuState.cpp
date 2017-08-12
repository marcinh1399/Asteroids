#include "stdafx.h"
#include "MenuState.h"


MenuState::MenuState(std::unique_ptr<StateManager> & u_manager,
	std::unique_ptr<sf::RenderWindow> & u_window, sf::Vector2f world_bounds,
	std::shared_ptr<KeyboardHandling> keyboard)
	: IState(u_manager, u_window, world_bounds, keyboard),
	button_factory(world_bounds)
{
	buttons.push_back(std::move(button_factory.makeMenuButton(PressButton::MenuType::play)));
	buttons.push_back(std::move(button_factory.makeMenuButton(PressButton::MenuType::options)));
	buttons.push_back(std::move(button_factory.makeMenuButton(PressButton::MenuType::exit)));
}



void MenuState::show()
{
	_window->clear();
	for (auto & button : buttons)
	{
		_window->draw(*(button->getSprite()));
	}
	_window->display();
}

void MenuState::update(const float & delta)
{
	///////
}

void MenuState::mouseHandle(const sf::Vector2i & v, const bool & pressed)
{
	std::shared_ptr<PressButton> clicked_button;
	bool clicked = false;

	if (mouse.stateChanged(v, pressed)) // this function update state too
	{
		sf::Vector2f vf(v);
		for (auto & button : buttons)
		{
			button->cursorOn(vf);
			if (mouse.buttonReleased())
			{
				clicked = button->clicked(vf);
			}

			if (clicked)
			{
				clicked_button = button;
				break;
			}
		}
	}


	if (clicked)
	{
		switch (clicked_button->getType())
		{
			case PressButton::MenuType::play:
				_manager->push(new GameState(_manager, _window, world_size, _keyboard));
				break;
			case PressButton::MenuType::options:
				break;
			case PressButton::MenuType::exit:	
				_manager->pop();
				break;
		}
	}

	
}

bool MenuState::isLoaded()
{
	return true;
}


MenuState::~MenuState()
{
}
