#include "stdafx.h"
#include "IListener.h"


IListener::IListener(std::shared_ptr<KeyboardHandling> keyboard)
	: _keyboard{ keyboard }
{
	_keyboard->registerListener(this);
}

IListener & IListener::operator+=(const sf::Keyboard::Key & key)
{
	keys.push_back(key);
	return *this;
}

void IListener::setList(std::list<sf::Keyboard::Key> & _keys)
{
	pressed_keys.clear();

	for (auto key : keys)
	{
		for (auto _key : _keys)
		{
			if (_key == key)
			{
				pressed_keys.push_back(_key);
			}
		}
	}

	handling();
}

IListener::~IListener()
{
}
