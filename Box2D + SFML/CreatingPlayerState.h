#pragma once
#include "IState.h"
#include <SFML\System.hpp>
#include "SpaceshipTypes.h"
#include "Ship.h"
#include <utility>


class CreatingPlayerState 
	: public IState, IListener
{
	
private:

	enum class State
	{
		nickname,
		spaceship
	};



	sf::String player_name;
	size_t string_index;
	
	SpaceshipTypes * spaceship_types;

	std::vector<Ship *> ships_to_choose;


	void loadShips();

	void setKeys();


	void typingNickname();

	void choosingShip();
	
	


public:
	CreatingPlayerState(std::unique_ptr<StateManager> & u_manager,
		std::unique_ptr<sf::RenderWindow> & u_window, sf::Vector2f world_bounds,
		std::shared_ptr<KeyboardHandling> keyboard);

	~CreatingPlayerState();

	// Inherited via IState
	virtual void show() override;
	virtual void update(const float & delta) override;
	virtual void mouseHandle(const sf::Vector2i & v, const bool & clicked) override;
	virtual bool isLoaded() override;

	// Inherited via IListener
	virtual void handling(const float & delta) override;
};

