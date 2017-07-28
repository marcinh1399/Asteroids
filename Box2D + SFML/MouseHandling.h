#pragma once
#include "SFML\Graphics.hpp"

class MouseHandling
{
private:

	struct Mouse
	{
		sf::Vector2i v{ -1, -1 };
		bool pressed{ false };

		void set(const sf::Vector2i & v, const bool & pressed)
		{
			this->v = v;
			this->pressed = pressed;
		}

		bool operator!=(const Mouse & m)
		{
			return this->v != m.v || this->pressed != m.pressed;
		}
	};

	Mouse last_state;
	Mouse current_state;


public:

	bool stateChanged(const sf::Vector2i & v, const bool & pressed);

	bool buttonReleased();

};

