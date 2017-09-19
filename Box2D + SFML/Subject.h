#pragma once
#include "Observer.h"
#include <list>

class Observer;
class Object;

class Subject
{

protected:

	std::list<Observer *> observers;

	virtual void notifyObservers();

public:

	Subject() = default;

	virtual void attach(Observer * observer);

	virtual void detach(Observer * observer);
};


