#include "stdafx.h"
#include "Subject.h"


void Subject::notifyObservers()
{
	for (auto observer : observers)
		observer->update();
}

void Subject::attach(Observer * observer)
{
	observers.push_back(observer);
}

void Subject::detach(Observer * observer)
{
	auto it = std::find(observers.begin(), observers.end(), observer);

	observers.erase(it);
}
