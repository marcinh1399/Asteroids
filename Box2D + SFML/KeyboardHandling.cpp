#include "stdafx.h"
#include "KeyboardHandling.h"


void KeyboardHandling::sendKeysToListeners(const float & delta)
{
	for (auto listener : listeners)
	{
		listener->setList(pressed_keys, delta);
	}
}


void KeyboardHandling::registerListener(IListener * listener)
{
	listeners.push_back(listener);
}

void KeyboardHandling::unregisterListener(IListener * listener)
{
	listeners.erase(std::find(listeners.begin(), listeners.end(), listener));
}

void KeyboardHandling::update(const float & delta)
{
	pressed_keys.clear();

	sf::Keyboard::Key key = sf::Keyboard::Key::A;
	
	while (key != sf::Keyboard::Key::KeyCount)
	{
		if (sf::Keyboard::isKeyPressed(key))
		{
			pressed_keys.push_back(key);
		}
		
		key = static_cast<sf::Keyboard::Key>(static_cast<int>(key) + 1);
	}

	sendKeysToListeners(delta);
}



KeyboardHandling::~KeyboardHandling()
{
	pressed_keys.clear();
	listeners.clear();
}
