#include "stdafx.h"
#include "WorldManager.h"



WorldManager::WorldManager(std::shared_ptr<GameObjects> g_objects)
	: game_objects(g_objects)
{
	bullet_handling = std::make_unique<BulletHandling>(game_objects);
	objects_manager = std::make_unique<ObjectManager>(game_objects);
}



void WorldManager::animations(const float & delta)
{
	game_objects->expl_animations.erase(
		std::remove_if(game_objects->expl_animations.begin(), game_objects->expl_animations.end(),
			[delta](std::unique_ptr<Animation> & animation) -> bool {
		return animation->getFrame(delta) == nullptr;
	}), game_objects->expl_animations.end());
}



void WorldManager::act(const float & delta)
{
	bullet_handling->update(delta);

	objects_manager->update(delta);

	game_objects->world->Step(delta, 8, 3);

	for (auto & o : game_objects->objects)
	{
		o->act(delta);
	}

	if (game_objects->enemy_bullet)
	{
		game_objects->enemy_bullet->act(delta);
		game_objects->objects.push_back(std::move(game_objects->enemy_bullet));
	}

	animations(delta);
}



WorldManager::~WorldManager()
{
}
