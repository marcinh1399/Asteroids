#pragma once
#include <SFML\Window.hpp>
#include <list>
#include <utility>
#include <vector>
#include "IListener.h"
#include <mutex>
#include <array>
#include <bitset>
#include <atomic>


class IListener;


class KeyboardHandling
{

private:
	
	std::bitset<101> pressed_keys;
	std::vector<IListener *> listeners;
	std::atomic<bool> turn_off_thread;

	void sendKeysToListeners();


public:

	KeyboardHandling();

	void registerListener(IListener * listener);

	void unregisterListener(IListener * listener);

	void update();

	void turnOffThread();

	~KeyboardHandling();
};

