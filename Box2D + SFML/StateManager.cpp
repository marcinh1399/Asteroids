#include "stdafx.h"
#include "StateManager.h"


StateManager::StateManager()
{
}

bool StateManager::push(IState * state)
{
	bool loaded = state->isLoaded();

	if (loaded)
	{
		states.push(state);
	}

	return loaded;
}

void StateManager::pop()
{
	if (!states.empty())
	{
		IState * state = states.top();
		states.pop();
		delete state;
	}
}

IState * StateManager::getCurrentState()
{
	IState * _state{ nullptr };

	if (!states.empty())
	{
		_state = states.top();
	}

	return _state;
}


StateManager::~StateManager()
{
}
