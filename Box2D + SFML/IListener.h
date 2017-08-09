#pragma once
#include "KeyboardHandling.h"
#include <SFML\Window.hpp>
#include <memory>
#include <list>
#include <array>


class KeyboardHandling;


class IListener
{

protected:

	std::shared_ptr<KeyboardHandling> _keyboard;
	std::vector<sf::Keyboard::Key> keys;
	std::list<sf::Keyboard::Key> pressed_keys;

	virtual void handling(const float & delta) = 0;

public:
	IListener(std::shared_ptr<KeyboardHandling> keyboard);

	IListener & operator+=(const sf::Keyboard::Key & key);

	void setList(std::list<sf::Keyboard::Key> & _keys, const float & delta);

	virtual ~IListener();
};

