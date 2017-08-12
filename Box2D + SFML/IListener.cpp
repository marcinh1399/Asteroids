#include "stdafx.h"
#include "IListener.h"


IListener::IListener(std::shared_ptr<KeyboardHandling> keyboard)
	: _keyboard{ keyboard }
{
	_keyboard->registerListener(this);
}


void IListener::setPressedKeys(std::bitset<101>& pressed_keys)
{
	pressed_keys_lock.lock();

	for (auto & pair : keys)
	{
		pair.second = pressed_keys[static_cast<int>(pair.first)];
	}

	pressed_keys_lock.unlock();
}

IListener::~IListener()
{	
	_keyboard->unregisterListener(this);
}
