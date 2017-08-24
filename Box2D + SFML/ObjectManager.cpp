#include "stdafx.h"
#include "ObjectManager.h"



ObjectManager::ObjectManager(std::shared_ptr<GameObjects> g_objects)
	: world_size(g_objects->world_size),
	objects(g_objects->objects),
	expl_animations(g_objects->expl_animations),
	world(g_objects->world),
	factory(g_objects->factory),
	game_objects(g_objects)
{
	addEnemy();
}

void ObjectManager::update(const float & delta)
{

		collisions();
		//removeObjects();
		addAsteroid(delta);
}



bool ObjectManager::isOutOfMap(std::unique_ptr<Object>& o)
{
	if (o->getState() == ObjectState::created)
		return false;

	return World::outOfMap(o->getPosition());
}

void ObjectManager::addAsteroid(const float & delta)
{
	asteroid_timer += delta;

	if (asteroids_on_map >= max_asteroids_on_map)
		return;

	if (asteroid_timer.use() || asteroids_on_map < asteroids_min)
	{
		if (rand() % 5 > 3)
		{
			objects.push_back(std::move(factory->makeAsteroid()));
			++asteroids_on_map;
		}
	}
}

void ObjectManager::addEnemy()
{
	auto enemy = factory->makeEnemy(game_objects);

	objects.push_back(std::move(enemy));
}

void ObjectManager::removeObjects()
{
	std::unique_ptr<b2World> & _world = world;
	int & asteroids = asteroids_on_map;
	auto end = std::remove_if(objects.begin(), objects.end(), [&](std::unique_ptr<Object> & o) -> bool {
		bool remove = o->getState() == ObjectState::dead || ObjectManager::isOutOfMap(o);

		if (remove)
		{
			if (dynamic_cast<Asteroid *>(o.get()) || dynamic_cast<Bullet *>(o.get()))
			{
				_world->DestroyBody(o->getBody());

				if (dynamic_cast<Asteroid *>(o.get()))
					--asteroids;
			}
				
			else
				remove = false;
		}

		return remove;
	});

	objects.erase(end, objects.end());
}

void ObjectManager::collisions()
{
	for (b2Contact * contact = world->GetContactList(); contact != nullptr; contact = contact->GetNext())
	{

		if (!contact->IsTouching())
			continue;

		b2Body * a = contact->GetFixtureA()->GetBody();
		Object * a_obj = static_cast<Object *>(a->GetUserData());
		b2Body * b = contact->GetFixtureB()->GetBody();
		Object * b_obj = static_cast<Object *>(b->GetUserData());

		if (dynamic_cast<Asteroid *>(a_obj) && dynamic_cast<Asteroid *>(b_obj))
			continue;

		bool a_destroyed = a_obj->hit(b_obj->getDamage());
		bool b_destroyed = b_obj->hit(a_obj->getDamage());

		if (a_destroyed)
			addExplosionAnimation(a_obj);

		if (b_destroyed)
			addExplosionAnimation(b_obj);
	}
}

void ObjectManager::addExplosionAnimation(Object * obj)
{
	float radius = obj->getShape()->getGlobalBounds().height / 2;
	std::unique_ptr<Animation> animation(new Animation(obj->getPosition(), radius, 1.f / 60.f, 10));
	expl_animations.push_back(std::move(animation));
}


ObjectManager::~ObjectManager()
{
}
