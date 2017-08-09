#pragma once
#include <SFML\Window.hpp>
#include <list>
#include <utility>
#include <vector>
#include "IListener.h"


class IListener;


class KeyboardHandling
{

private:
	
	std::list<sf::Keyboard::Key> pressed_keys;
	std::vector<IListener *> listeners;

	void sendKeysToListeners(const float & delta);


public:

	void registerListener(IListener * listener);

	void unregisterListener(IListener * listener);

	void update(const float & delta);

	~KeyboardHandling();
};

