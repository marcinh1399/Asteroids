#pragma once
#include "Observer.h"
#include "Object.h"
#include "ArmedObject.h"


class MissileObserver :
	public Observer
{

private:

	ArmedObject::Missile missile;


public:

	MissileObserver(ArmedObject * subject);

	virtual void update() override;

	virtual void getState(State & update) override;

	virtual void clear() override;
};

