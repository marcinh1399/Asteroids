#pragma once
#include "Object.h"
#include <vector>
#include <memory>
#include "Box2D\Box2D.h"
#include "AsteroidGenerator.h"
#include "Bullet.h"
#include "TimeManager.h"
#include "PlayerBuilder.h"


class WorldManager
{

private:


	std::vector< std::unique_ptr<Object> > & objects;
	std::vector< std::unique_ptr<Animation> > & expl_animations;
	

	std::unique_ptr<Player> player;

	std::unique_ptr<b2World> _world;
	std::unique_ptr<AsteroidGenerator> _generator;
	std::shared_ptr<KeyboardHandling> _keyboard;

	int screen_width = 1920;
	int screen_height = 1200;

	int asteroids_on_map{ 0 };
	const int max_asteroids_on_map{ 20 };

	TimeManager time_manager{ 1.f, true };

	void newAsteroid(const float & delta);

	void removeAsteroid();

	void contact();

	void animations(const float & delta);


public:

	int world_width;
	int world_height;

	WorldManager(int screen_width, int screen_height, 
		std::vector< std::unique_ptr<Object> > & v_objects, 
		std::vector< std::unique_ptr<Animation> > & v_explosions,
		std::shared_ptr<KeyboardHandling> keyboard);
	
	bool outsideMap(const std::unique_ptr<Object> & o);

	void act(const float & delta);

	~WorldManager();
};

