#include "stdafx.h"
#include "PositionObserver.h"



PositionObserver::PositionObserver(Object * subject)
	: Observer(subject)
{
	_subject->attach(this);
}

void PositionObserver::update()
{
	auto ptr = static_cast<Object *>(_subject);

	b2position = ptr->getB2position();
	sfposition = ptr->getSFposition();
}

void PositionObserver::getState(State & update)
{
	update.b2position = b2position;
	update.sfposition = sfposition;
}
