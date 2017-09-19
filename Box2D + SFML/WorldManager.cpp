#include "stdafx.h"
#include "WorldManager.h"




void WorldManager::initACM()
{
	acm.current_quantity = 0;
	acm.min_quantity = 30;
	acm.max_quantity = 100;
	acm.min_value_of_rand = 700;
	acm.range_of_rand = 1000;
	acm.timer = TimeManager(1.f, false);
}


void WorldManager::initECM()
{
	ecm.current_quantity = 0;
	ecm.min_quantity = 0;
	ecm.max_quantity = 3;
	ecm.min_value_of_rand = 980;
	ecm.range_of_rand = 1000;
	ecm.timer = TimeManager(30.f, false);
}


void WorldManager::makeAsteroid(const float & delta)
{
	if (!acm.createObject(delta))
		return;
		

	auto object = factory.makeAsteroid();
	auto key = object->getBody();

	add(key, object);
}


void WorldManager::makeEnemy(const float & delta)
{
	if (!ecm.createObject(delta))
		return;

	auto object = factory.makeEnemy();
	auto key = object->getBody();

	add(key, object);
}


void WorldManager::add(b2Body * key, Object * object)
{
	ObserversController * controller = new ObserversController();

	controller->addObserver(new ObjectStateObserver(object));
	controller->addObserver(new PositionObserver(object));

	if (auto armed_object = dynamic_cast<ArmedObject *>(object))
		controller->addObserver(new MissileObserver(armed_object));


	set_of_objects.observers[key] = controller;
	set_of_objects.objects[key] = object;
}


void WorldManager::collisions()
{
	for (b2Contact * contact = b2world.GetContactList(); contact != nullptr; contact = contact->GetNext())
	{

		if (!contact->IsTouching())
			continue;

		b2Body * a = contact->GetFixtureA()->GetBody();
		b2Body * b = contact->GetFixtureB()->GetBody();

		Object * a_obj = set_of_objects.objects[a];
		Object * b_obj = set_of_objects.objects[b];

		if (dynamic_cast<Asteroid *>(a_obj) && dynamic_cast<Asteroid *>(b_obj))
			continue;

		bool a_destroyed = a_obj->hit(b_obj->getDamage());
		bool b_destroyed = b_obj->hit(a_obj->getDamage());

		if (a_destroyed) 
			explosion(a_obj);

		if (b_destroyed)
			explosion(b_obj);
	}
}


void WorldManager::explosion(Object * obj)
{
	float radius = obj->getRadius();
	Animation animation(obj->getSFposition(), radius, 1.f / 60.f, 10);
	set_of_objects.explosions.push_back(std::move(animation));
}


void WorldManager::remove()
{
	auto & world = b2world;
	auto & asteroids = acm.current_quantity;
	auto & enemies = ecm.current_quantity;
	auto & map_of_object = set_of_objects.objects;
	auto & map_of_observers = set_of_objects.observers;


	auto func = [&](auto & iterator) -> bool {

		auto state = iterator->second->getState();

		bool remove = this->outOfMap(state) || state.object_state == ObjectState::dead;

		if (!remove)
			return false;

		auto key = iterator->first;


		if (dynamic_cast<PlayerObject *>(map_of_object[key]) || dynamic_cast<EnemyAI *>(map_of_object[key]))
			return false;


		if (dynamic_cast<Asteroid *>(map_of_object[key]))
			--asteroids;
		else if (dynamic_cast<EnemyAI *>(map_of_object[key]))
			--enemies;

		world.DestroyBody(key);

		return true;
	};


	for (auto iter = map_of_observers.begin(); iter != map_of_observers.end();)
	{
		if (func(iter))
			iter = map_of_observers.erase(iter);
		else
			++iter;
	}

/*
	for (auto & pair : map_of_observers)
	{
		if (func(pair))

	}



	auto end = std::remove_if(map_of_observers.begin(), map_of_observers.end(),
		[&](auto & iterator) -> bool {

		auto state = iterator->second->getState();

		bool remove = this->outOfMap(state) || state.object_state == ObjectState::dead;

		if (!remove)
			return false;

		auto key = iterator->first;


		if (dynamic_cast<PlayerObject *>(map_of_object[key]))
			return false;


		if (dynamic_cast<Asteroid *>(map_of_object[key]))
			--asteroids;
		else if (dynamic_cast<EnemyAI *>(map_of_object[key]))
			--enemies;

		world.DestroyBody(key);

		return true;
	});

	map_of_observers.erase(end, map_of_observers.end());

	
	auto end2 = std::remove_if(map_of_object.begin(), map_of_object.end(),
		[&](auto & iterator) -> bool {

		auto key = iterator->first;

		return !map_of_observers.count(key);
	});

	map_of_object.erase(end2, map_of_object.end());

	*/


	auto func2 = [&](auto & iterator) -> bool {

		auto key = iterator->first;

		return !map_of_observers.count(key);
	};

	
	for (auto iter = map_of_object.begin(); iter != map_of_object.end();)
	{
		if (func2(iter))
			iter = map_of_object.erase(iter);
		else
			++iter;
	}

}


void WorldManager::missile()
{
	std::vector<std::pair<b2Body *, Object *>> missiles;

	std::for_each(set_of_objects.observers.begin(), set_of_objects.observers.end(), [&](auto & pair) -> void {

		auto bullet = pair.second->getState().missile;

		auto key = pair.first;

		if (bullet.fire)
		{
			auto object = set_of_objects.objects[key];

			if (auto armed_object = dynamic_cast<ArmedObject *>(object))
			{

				auto new_missile = factory.makeBullet(bullet.type_of_missile, armed_object, bullet.dmg_multiplier);
				auto missile_key = new_missile->getBody();


				missiles.push_back(std::pair<b2Body *, Object *>(missile_key, new_missile));
			}
		}

	});
		

	for (auto & pair : missiles)
	{
		add(pair.first, pair.second);
	}
		
}


WorldManager::WorldManager(GameObjects & game_objects, std::shared_ptr<KeyboardHandling> keyboard)
	: set_of_objects(game_objects),
	b2world(b2Vec2{ 0.f, 0.f }),
	factory(b2world, game_objects)
{
	initACM();
	initECM();

	PlayerObject * player = factory.makePlayer(sf::Vector2f(World::radius, World::radius), 
		keyboard, SpaceshipTypes::ShipType::type1);
	add(player->getBody(), player);

	EnemyAI * enemy = factory.makeEnemy();
	enemy->setTarget(player->getBody());
	add(enemy->getBody(), enemy);
}



void WorldManager::act(const float & delta)
{
	makeAsteroid(delta);
	makeEnemy(delta);
	collisions();
	remove();

	std::for_each(set_of_objects.observers.begin(), set_of_objects.observers.end(), [](auto & pair) -> void {
		pair.second->clear();
	});

	b2world.Step(delta, 8, 3);

	std::for_each(set_of_objects.objects.begin(), set_of_objects.objects.end(), [=](auto & pair) -> void {
		pair.second->act(delta);
	});


	missile();
}



bool WorldManager::outOfMap(Object & o)
{
	if (o.getState() == ObjectState::created)
		return false;

	return World::outOfMap(o.getSFposition());
}


bool WorldManager::outOfMap(const Observer::State & state)
{
	if (state.object_state == ObjectState::created)
		return false;

	return World::outOfMap(state.sfposition);
}


WorldManager::~WorldManager()
{
}





/*

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

*/


