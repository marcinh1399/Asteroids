#pragma once
#include "KeyboardHandling.h"
#include <SFML\Window.hpp>
#include <memory>
#include <list>
#include <array>
#include <mutex>
#include <utility>
#include <bitset>


class KeyboardHandling;


class IListener
{

protected:

	std::shared_ptr<KeyboardHandling> _keyboard;
	std::vector<std::pair<sf::Keyboard::Key, bool>> keys;

	std::mutex pressed_keys_lock;

	virtual void handling(const float & delta) = 0;

public:
	IListener(std::shared_ptr<KeyboardHandling> keyboard);
	
	void setPressedKeys(std::bitset<101> & pressed_keys);

	virtual ~IListener();
};

