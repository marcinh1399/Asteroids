#pragma once
#include "Subject.h"
#include "ObjectState.h"
#include "Bullet.h"

#include "ArmedObject.h"


class Subject;

class Observer
{

protected:

	Subject * _subject;
	
public:

	struct State
	{
		ObjectState object_state;
		ArmedObject::Missile missile;
		b2Vec2 b2position;
		sf::Vector2f sfposition;

		void reset()
		{
			missile.reset();
		}
	};


	Observer(Subject * subject);

	virtual void update() = 0;

	virtual void getState(State & update) = 0;

	virtual void clear();
};