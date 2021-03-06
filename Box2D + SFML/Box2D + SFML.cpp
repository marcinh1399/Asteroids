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
#include "IState.h"
#include "MenuState.h"
#include "StateManager.h"
#include "GameState.h"
#include <wtypes.h>
#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include "KeyboardHandling.h"
#include "SpaceshipTypes.h"
#include "OpeningState.h"
#include <ctime>
#include <cstdio>


#include <thread>


#include <boost\thread.hpp>


#include <boost\ptr_container\ptr_vector.hpp>



#include <boost\ptr_container\ptr_map.hpp>
#include <boost\ptr_container\ptr_inserter.hpp>



#include "Coords.h"


#define NDEBUG


#define M_PI 3.14159265359



float Coords::to_world = 20.f;
float Coords::to_screen = 1.f / 20.f;
float Coords::m_pi = 3.14f;
SpaceshipTypes * SpaceshipTypes::instance = nullptr;

void foo(int n)
{
	while (n--)
	{
		printf("thread1; %d\n", n);
	}
}

class CLASS
{
public:

	int x = 100;

	CLASS();
	~CLASS();

private:

};

CLASS::CLASS()
{
	printf("CLASS is creating!\n");
}

CLASS::~CLASS()
{
	printf("CLASS is destroying!\n");
}


class KEY
{
public:

	int key = 214190248;

	KEY();
	~KEY();

private:

};

KEY::KEY()
{
	printf("KEY is creating!\n");
}

KEY::~KEY()
{
	printf("KEY is destroying!\n");
}


int main(int argc, char** argv)
{

	srand(time(NULL));
	Coords::init(20);

	
	KEY * ptr;
	

	if (true)
	{
		
		boost::ptr_map<KEY *, CLASS> ptr_map;
		KEY * key = ptr = new KEY();
		CLASS * object = new CLASS();

		ptr_map.insert(key, object);
	}


	
	
	
/**/
	RECT desktop;
	const HWND Desktop = GetDesktopWindow();
	GetWindowRect(Desktop, &desktop);
	int width = desktop.right;
	int height = desktop.bottom;

	


	printf("WIDTH: %d\nHEIGTH: %d\n\n\n\n", width, height);


	sf::Vector2f world_size(width, height);


	srand(time(NULL));

	std::unique_ptr<sf::RenderWindow> _window(new sf::RenderWindow(sf::VideoMode(1920, 1200, 32), "Asteroids!", sf::Style::Fullscreen));
	std::unique_ptr<StateManager> _state_manager(new StateManager());

	sf::View viewport(sf::Vector2f(960.f, 600.f), sf::Vector2f(1920.f, 1200.f));
	_window->setView(viewport);

	
	std::shared_ptr<KeyboardHandling> keyboard = std::make_shared<KeyboardHandling>();
	


	IState * _opening = new OpeningState(_state_manager, _window, world_size, keyboard);

	_state_manager->push(_opening);

	IState * _state = _state_manager->getCurrentState();

	
	sf::Thread t_keyboard(&KeyboardHandling::update, keyboard.get());
	t_keyboard.launch();

	sf::Clock clock;
	clock.restart();

	for (int i = 0; (_state = _state_manager->getCurrentState()) != nullptr; ++i)
	{
		sf::Time time = sf::seconds(1.f / 60.f);
		while (clock.getElapsedTime() < time);

		_state->mouseHandle(sf::Mouse::getPosition(), sf::Mouse::isButtonPressed(sf::Mouse::Left));
		if (_state = _state_manager->getCurrentState()) {
			_state->update(clock.restart().asSeconds());
			if (_state = _state_manager->getCurrentState())
				_state->show();
		}

	
	}
	
	keyboard->turnOffThread();
	t_keyboard.wait();
	/**/

	while (true)
		;
	return 0;
}
