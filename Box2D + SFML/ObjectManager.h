#pragma once
#include <vector>
#include <memory>
#include "Object.h"
#include "Asteroid.h"
#include "Box2D\Box2D.h"
#include <atomic>
#include "Factory.h"
#include "SFML\Graphics.hpp"
#include "GameObjects.h"
#include "World.h"
#include "Enemy.h"


class ObjectManager
{

private:

	sf::Vector2f world_size;

	std::vector< std::unique_ptr<Object> > & objects;
	std::vector< std::unique_ptr<Animation> > & expl_animations;
	std::unique_ptr<b2World> & world;
	std::unique_ptr<Factory> & factory;

	std::shared_ptr<GameObjects> game_objects;


	int asteroids_on_map{ 0 };
	const int max_asteroids_on_map{ 100 };
	const int asteroids_min{ 50 };
	TimeManager asteroid_timer{ 1.f, true };

	
	void addAsteroid(const float & delta);

	void addEnemy();

	void removeObjects();

	void collisions();

	void addExplosionAnimation(Object * obj);


public:

	ObjectManager(std::shared_ptr<GameObjects> g_objects);

	void update(const float & delta);

	bool isOutOfMap(std::unique_ptr<Object> & o);

	~ObjectManager();
};

