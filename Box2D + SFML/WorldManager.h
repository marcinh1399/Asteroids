#pragma once
#include "Object.h"
#include <vector>
#include <memory>
#include "Box2D\Box2D.h"
#include "AsteroidGenerator.h"

class WorldManager
{

private:

	std::vector<Object *> & objects;
	std::unique_ptr<b2World> _world;
	std::unique_ptr<AsteroidGenerator> _generator;

	int screen_width;
	int screen_height;


	int asteroids_on_map{ 0 };
	const int max_asteroids_on_map{ 20 };
	float time_since_last_asteroid{ INFINITY };

	void newAsteroid(const float & delta);

	void removeAsteroid();

	inline bool outsideMap(Object * o);

	void contact();


public:

	WorldManager(int screen_width, int screen_height, std::vector<Object *> & objects);
	
	void act(const float & delta);

	~WorldManager();
};

