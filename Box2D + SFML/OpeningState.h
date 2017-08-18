#pragma once
#include "IState.h"
#include <string>
#include <SFML\Graphics.hpp>
#include <memory>
#include "KeyboardHandling.h"
#include "StateManager.h"
#include "TimeManager.h"
#include "GameState.h"
#include "MenuState.h"


class OpeningState :
	public IState
{

private:

	const std::string path_to_bg = "opening_image.png";

	sf::Texture texture;
	sf::Sprite background;

	TimeManager time_manager{ 3.f, false };
	bool first_state{ true };

	void nextState();


public:
	OpeningState(std::unique_ptr<StateManager> & u_manager,
		std::unique_ptr<sf::RenderWindow> & u_window, sf::Vector2f world_bounds,
		std::shared_ptr<KeyboardHandling> keyboard);

	~OpeningState();

	// Inherited via IState
	virtual void show() override;
	virtual void update(const float & delta) override;
	virtual void mouseHandle(const sf::Vector2i & v, const bool & clicked) override;
	virtual bool isLoaded() override;
};

