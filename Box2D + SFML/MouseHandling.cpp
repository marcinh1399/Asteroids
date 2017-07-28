#include "stdafx.h"
#include "MouseHandling.h"


bool MouseHandling::stateChanged(const sf::Vector2i & v, const bool & pressed)
{
	last_state = current_state;
	current_state.set(v, pressed);
	
	return last_state != current_state;
}

bool MouseHandling::buttonReleased()
{
	return last_state.pressed && !current_state.pressed;
}

