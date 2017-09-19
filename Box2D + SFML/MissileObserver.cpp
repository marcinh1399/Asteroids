#include "stdafx.h"
#include "MissileObserver.h"




MissileObserver::MissileObserver(ArmedObject * subject)
	: Observer(subject)
{
	_subject->attach(this);

	missile.reset();
}


void MissileObserver::update()
{
	missile = static_cast<ArmedObject *>(_subject)->getMissile();
}

void MissileObserver::getState(State & update)
{
	update.missile = missile;
}

void MissileObserver::clear()
{
	missile.reset();
}