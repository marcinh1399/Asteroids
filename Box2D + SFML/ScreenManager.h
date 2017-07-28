#pragma once
#include "Object.h"
#include <vector>
#include <memory>

class ScreenManager
{

private:

	std::vector<Object *> & objects;
	std::unique_ptr<sf::RenderWindow> & _window;

public:

	ScreenManager(std::vector<Object *> & v_objects, std::unique_ptr<sf::RenderWindow> & u_window);

	void display();

	~ScreenManager();
};

