#pragma once
#include "Observer.h"
class ObjectStateObserver :
	public Observer
{

private:

	ObjectState state;

public:

	ObjectStateObserver(Object * subject);

	virtual void update() override;

	virtual void getState(State & update) override;
};

