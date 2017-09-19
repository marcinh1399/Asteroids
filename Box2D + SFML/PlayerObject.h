#pragma once
#include "IListener.h"
#include "ArmedObject.h"
#include <memory>


class PlayerObject :
	public IListener, public ArmedObject
{

private:

	virtual void move(const float & delta, int move, int turn);

public:

	PlayerObject(b2Body * body, sf::Shape * shape, Statistics statistics, std::shared_ptr<KeyboardHandling> keyboard);
	
	virtual ~PlayerObject();

	// Inherited via IListener
	virtual void handling(const float & delta) override;

	// Inherited via ArmedObject
	virtual void act(const float & delta) override;
};

