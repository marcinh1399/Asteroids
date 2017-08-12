#pragma once
#include <Stack>
#include "IState.h"

class IState;

class StateManager
{

private:
	std::stack<IState *> states;


public:
	StateManager();

	bool push(IState * state);

	void pop();

	IState * getCurrentState();

	~StateManager();
};

