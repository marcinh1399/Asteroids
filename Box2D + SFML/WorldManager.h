#pragma once
#include "Object.h"
#include <vector>
#include <memory>
#include "Box2D\Box2D.h"
#include "AsteroidGenerator.h"
#include "Bullet.h"
#include "TimeManager.h"
#include "Factory.h"
#include "BulletHandling.h"
#include "ObjectManager.h"
#include "GameObjects.h"


class WorldManager
{

private:

/*
	std::vector< std::unique_ptr<Object> > & objects;
	std::vector< std::unique_ptr<Animation> > & expl_animations;

	std::shared_ptr<Player> player;

	std::unique_ptr<b2World> _world;
	std::unique_ptr<Factory> _factory;
	std::shared_ptr<KeyboardHandling> _keyboard;

	*/

	std::unique_ptr<BulletHandling> bullet_handling;
	std::unique_ptr<ObjectManager> objects_manager;
	
	std::shared_ptr<GameObjects> game_objects;




	int screen_width = 1920;
	int screen_height = 1200;

	int asteroids_on_map{ 0 };
	const int max_asteroids_on_map{ 20 };

	TimeManager time_manager{ 1.f, true };

	void animations(const float & delta);


public:

	int world_width;
	int world_height;



	WorldManager(std::shared_ptr<GameObjects> g_objects);
	


	void act(const float & delta);

	~WorldManager();
};

