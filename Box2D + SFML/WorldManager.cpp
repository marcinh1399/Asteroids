#include "stdafx.h"
#include "WorldManager.h"


void WorldManager::newAsteroid(const float & delta)
{
	time_since_last_asteroid += delta;

	if (asteroids_on_map >= max_asteroids_on_map)
		return;

	if (time_since_last_asteroid > 1.5f || asteroids_on_map < 6)
	{
		if (rand() % 100 > 85)
		{
			Object * asteroid = _generator->makeAsteroid();
			objects.push_back(asteroid);
			asteroids_on_map++;
			time_since_last_asteroid = 0;
		}
	}
}

void WorldManager::removeAsteroid()
{
	for (auto it = objects.begin(); it != objects.end();)
	{
		if ((*it)->isReadyToRemove() && outsideMap(*it))
		{
			it = objects.erase(it);
			asteroids_on_map--;
		}
		else
		{
			it++;
		}
	}
}

bool WorldManager::outsideMap(Object * o)
{
	sf::Vector2f v = o->getPosition();
	return v.x < -250 || v.x > screen_width + 250
		|| v.y < -250 || v.y > screen_height + 250;
}

void WorldManager::contact()
{

	for (b2Contact * contact = _world->GetContactList(); contact != nullptr; contact = contact->GetNext())
	{
		b2Body * a = contact->GetFixtureA()->GetBody();
		Object * aObj = reinterpret_cast<Object *>(a->GetUserData());
		if (contact->IsTouching())
			aObj->getShape()->setOutlineColor(sf::Color::Red);
			
		
		b2Body * b = contact->GetFixtureB()->GetBody();
		Object * bObj = reinterpret_cast<Object *>(b->GetUserData());
		if (contact->IsTouching())
			bObj->getShape()->setOutlineColor(sf::Color::Green);
	}
}

WorldManager::WorldManager(int screen_width, int screen_height, std::vector<Object *> & v_objects)
	: objects(v_objects)
{
	_world = std::make_unique<b2World>(b2Vec2{ 0.f, 0.f });
	_generator = std::make_unique<AsteroidGenerator>(_world, screen_width, screen_height);
	this->screen_width = screen_width;
	this->screen_height = screen_height;
}

void WorldManager::act(const float & delta)
{
	newAsteroid(delta);

	_world->Step(delta, 8, 3);

	contact();

	for (Object * o : objects)
	{
		o->act(delta);
	}

	removeAsteroid();
}



WorldManager::~WorldManager()
{
}
