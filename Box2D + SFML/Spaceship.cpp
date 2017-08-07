#include "stdafx.h"
#include "Spaceship.h"


void Spaceship::setEq()
{
	equipment[0].makeHP();
	equipment[1].makeEngine();
	equipment[2].makeAgility();
	equipment[3].makeArmor();
	equipment[4].makeBullet();
	equipment[5].makeGun();
}

void Spaceship::animationOfReborn(const float & delta)
{
	immune_time += delta;
	_shape = _animation->getFrame(delta);

	if (immune_time.use())
	{
		_shape = _copy_of_shape;
		state = ObjectState::alive;
		//printf("CTKMB\n");
	}
}


Spaceship::Spaceship(float hp, b2Body * ptr_body, sf::Shape * ptr_shape, float dmg, Statistics statistics)
	: Object{ hp, ptr_body, ptr_shape, dmg }
{
	state = ObjectState::immune;
	_body->SetUserData(this);
	_copy_of_shape = ptr_shape;
	sf::ConvexShape * shape = dynamic_cast<sf::ConvexShape *>(_shape);
	sf::Shape * first = new sf::ConvexShape(*shape);
	first->setOutlineColor(sf::Color::Transparent);
	sf::Shape * second = new sf::ConvexShape(*shape);
	std::vector<sf::Shape *> frames;
	frames.push_back(first);
	frames.push_back(second);
	_animation = new Animation(frames, 0.15f, true);
}

bool Spaceship::improveHP()
{
	return equipment[0].nextLevel();;
}

bool Spaceship::improveEngine()
{
	return equipment[1].nextLevel();
}

bool Spaceship::improveAgility()
{
	return equipment[2].nextLevel();
}

bool Spaceship::improveArmor()
{
	return equipment[3].nextLevel();
}

bool Spaceship::improveBullet()
{
	return equipment[4].nextLevel();
}

bool Spaceship::improveGun()
{
	return equipment[5].nextLevel();
}


void Spaceship::act(const float & delta)
{
	
	
	if (state == ObjectState::immune)
	{
		animationOfReborn(delta);
	}

	updatePosition();
}


Spaceship::~Spaceship()
{
	delete _animation;
}

