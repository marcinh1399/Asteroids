#include "stdafx.h"
#include <stdio.h>
#include <cstdlib>
#include "Box2D\Box2D.h"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "Asteroid.h"
#include "Object.h"
#include <algorithm>
#include <cmath>
#include <memory>
#include "AsteroidGenerator.h"
#include <vector>
#include <assert.h>
#include "Object.h"
#include "WorldManager.h"
#include "ButtonGenerator.h"
#include "IState.h"
#include "MenuState.h"
#include "StateManager.h"
#include "GameState.h"
#include <wtypes.h>
#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include "KeyboardHandling.h"
#include "SpaceshipTypes.h"


#include "Coords.h"


#define NDEBUG


#define M_PI 3.14159265359



float Coords::to_world = 20.f;
float Coords::to_screen = 1.f / 20.f;
float Coords::m_pi = 3.14f;
SpaceshipTypes * SpaceshipTypes::instance = nullptr;

int main(int argc, char** argv)
{
	Coords::init(20);
	

	RECT desktop;
	const HWND Desktop = GetDesktopWindow();
	GetWindowRect(Desktop, &desktop);
	int width = desktop.right;
	int height = desktop.bottom;


	printf("WIDTH: %d\nHEIGTH: %d\n\n\n\n", width, height);


	srand(time(NULL));

	std::unique_ptr<sf::RenderWindow> _window(new sf::RenderWindow(sf::VideoMode(1920, 1200, 32), "Asteroids!", sf::Style::Fullscreen));
	std::unique_ptr<StateManager> _state_manager(new StateManager());

	
	std::shared_ptr<KeyboardHandling> keyboard = std::make_shared<KeyboardHandling>();

	IState * _menu = new MenuState(_state_manager, _window, width, height, keyboard);

	_state_manager->push(_menu);

	IState * _state = _state_manager->getCurrentState();
	IState * _g_state = new GameState(_state_manager, _window, width, height, keyboard);

	for (int i = 0;; ++i)
	{
		if (i == 2)
		{
			_state_manager->push(_g_state);
		}

		if (i == 120000)
		{
			_state_manager->removeCurrentState();
		}
		
		sf::Clock clock;
		clock.restart();
		sf::Time time = sf::seconds(1.f / 60.f);
		while (clock.getElapsedTime() < time);
		keyboard->update(1.f / 60.f);
		_state = _state_manager->getCurrentState();
		_state->mouseHandle(sf::Mouse::getPosition(), sf::Mouse::isButtonPressed(sf::Mouse::Left));
		_state->update(clock.getElapsedTime().asSeconds());
		_state->show();

	
	}


	return 0;
}
