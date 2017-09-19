#pragma once
#include "Observer.h"
#include "MissileObserver.h"
#include "ObjectStateObserver.h"
#include "PositionObserver.h"
#include <list>





class ObserversController
{

private:

	std::list<Observer *> observers;

public:
	ObserversController() = default;

	void addObserver(Observer * observer);

	Observer::State getState();

	void clear();
};

