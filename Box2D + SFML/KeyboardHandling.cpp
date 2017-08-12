#include "stdafx.h"
#include "KeyboardHandling.h"


void KeyboardHandling::sendKeysToListeners()
{
	for (auto listener : listeners)
	{
		listener->setPressedKeys(pressed_keys);
	}
}


KeyboardHandling::KeyboardHandling()
{
	turn_off_thread.store(false);
}

void KeyboardHandling::registerListener(IListener * listener)
{
	listeners.push_back(listener);
}

void KeyboardHandling::unregisterListener(IListener * listener)
{
	listeners.erase(std::find(listeners.begin(), listeners.end(), listener));
}

void KeyboardHandling::update()
{
	while (!turn_off_thread.load())
	{
		bool change = false;

		for (int i = 0; i < pressed_keys.size(); ++i)
		{
			if (pressed_keys[i] != sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
			{
				change = true;
				pressed_keys[i] = !pressed_keys[i];
			}
		}

		if (change) 
		{
			sendKeysToListeners();
		}
	}
}

void KeyboardHandling::turnOffThread()
{
	turn_off_thread.store(true);
}



KeyboardHandling::~KeyboardHandling()
{
	listeners.clear();
}
