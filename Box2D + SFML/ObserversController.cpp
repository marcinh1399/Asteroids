#include "stdafx.h"
#include "ObserversController.h"



void ObserversController::addObserver(Observer * observer)
{
	observers.push_back(observer);

	for (auto & obs : observers)
		obs->update();
}


Observer::State ObserversController::getState()
{
	Observer::State state;

	state.missile.reset();

	for (auto & observer : observers)
		observer->getState(state);

	return state;
}

void ObserversController::clear()
{
	for (auto & observer : observers)
		observer->clear();
}

