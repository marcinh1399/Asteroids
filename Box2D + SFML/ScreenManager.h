#pragma once
#include "Object.h"
#include <vector>
#include <memory>

class ScreenManager
{

private:

	std::vector<std::unique_ptr<Object>> & objects;
	std::vector< std::unique_ptr<Animation> > & expl_animations;
	std::unique_ptr<sf::RenderWindow> & _window;


public:

	ScreenManager(std::vector<std::unique_ptr<Object>> & v_objects, 
		std::vector< std::unique_ptr<Animation> > & v_explosions,
		std::unique_ptr<sf::RenderWindow> & u_window);

	void display();

	~ScreenManager();
};

