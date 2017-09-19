#include "stdafx.h"
#include "ObjectStateObserver.h"


ObjectStateObserver::ObjectStateObserver(Object * subject)
	: Observer(subject)
{
	_subject->attach(this);
}


void ObjectStateObserver::update()
{
	state = static_cast<Object *>(_subject)->getState();
}

void ObjectStateObserver::getState(State & update)
{
	update.object_state = state;
}


