#include "stdafx.h"
#include "OpeningState.h"



void OpeningState::nextState()
{
	if (first_state)
	{
		// if (exist serialization file of game)
			_manager->push(new MenuState(_manager, _window, world_size, _keyboard));
		// else
			// _manager->push(new 

		first_state = false;
	}
	else
	{
		_manager->pop();
	}
}

OpeningState::OpeningState(std::unique_ptr<StateManager>& u_manager, std::unique_ptr<sf::RenderWindow>& u_window, sf::Vector2f world_bounds, std::shared_ptr<KeyboardHandling> keyboard)
	: IState(u_manager, u_window, world_bounds, keyboard)
{
	texture.loadFromFile(path_to_bg);

	background.setTexture(texture);
	background.setPosition(0.f, 0.f);
}

OpeningState::~OpeningState()
{
}

void OpeningState::show()
{
	_window->clear();

	_window->draw(background);

	_window->display();
}

void OpeningState::update(const float & delta)
{
	time_manager += delta;

	if (time_manager.use()) {
		nextState();
	}
}

void OpeningState::mouseHandle(const sf::Vector2i & v, const bool & clicked)
{
}

bool OpeningState::isLoaded()
{
	return true;
}
