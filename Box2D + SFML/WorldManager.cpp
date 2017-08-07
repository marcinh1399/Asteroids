#include "stdafx.h"
#include "WorldManager.h"


void WorldManager::newAsteroid(const float & delta)
{
	time_manager += delta;

	if (asteroids_on_map >= max_asteroids_on_map)
		return;

	if (time_manager.isReady() > 1.5f || asteroids_on_map < 6)
	{
		if (rand() % 100 > 85)
		{
			std::unique_ptr<Object> ptr(_generator->makeAsteroid());
			objects.push_back(std::move(ptr));
			asteroids_on_map++;
			time_manager.use();
			printf("asteroids: %d | objects: %d\n\n", asteroids_on_map, objects.size());
		}
	}
}

void WorldManager::removeAsteroid()
{
	
	size_t removed_asteroids{ 0 };

	objects.erase(std::remove_if(objects.begin(), objects.end(), 
		[this, &removed_asteroids](std::unique_ptr<Object> & o) -> bool {
		bool toDelete = (o->getState() != ObjectState::created && this->outsideMap(o))
			|| o->getState() == ObjectState::dead;
		
		if (toDelete)
		{
			if (dynamic_cast<Asteroid *>(o.get()))
			{
				++removed_asteroids;
				_world->DestroyBody(o->getBody());
			}
			else
			{
				toDelete = false;
			}
		}
		
		return toDelete;
	}), objects.end());

	asteroids_on_map -= removed_asteroids;
}

bool WorldManager::outsideMap(const std::unique_ptr<Object> & o)
{
	sf::Vector2f v = o->getPosition();
	return v.x < -250 || v.x > screen_width + 250
		|| v.y < -250 || v.y > screen_height + 250;
}

void WorldManager::contact()
{

	for (b2Contact * contact = _world->GetContactList(); contact != nullptr; contact = contact->GetNext())
	{

		if (!contact->IsTouching())
		{
			continue;
		}



		b2Body * a = contact->GetFixtureA()->GetBody();
		Object * a_obj = static_cast<Object *>(a->GetUserData());
		b2Body * b = contact->GetFixtureB()->GetBody();
		Object * b_obj = static_cast<Object *>(b->GetUserData());

		if (dynamic_cast<Asteroid *>(a_obj) && dynamic_cast<Asteroid *>(b_obj))
		{
			continue;
		}
		
		
		bool a_destroyed = a_obj->hit(b_obj->getDamage());
		bool b_destroyed = b_obj->hit(a_obj->getDamage());

		if (a_destroyed)
		{
			float radius = a_obj->getShape()->getGlobalBounds().height / 2;
			std::unique_ptr<Animation> animation(new Animation(a_obj->getPosition(), radius, 1.f/60.f, 10));
			expl_animations.push_back(std::move(animation));
		}

		if (b_destroyed)
		{
			float radius = b_obj->getShape()->getGlobalBounds().height / 2;
			std::unique_ptr<Animation> animation(new Animation(b_obj->getPosition(), radius, 1.f / 60.f, 10));
			expl_animations.push_back(std::move(animation));
		}
	}
}

void WorldManager::animations(const float & delta)
{
	expl_animations.erase(
		std::remove_if(expl_animations.begin(), expl_animations.end(),
			[delta](std::unique_ptr<Animation> & animation) -> bool {
		return animation->getFrame(delta) == nullptr;
	}), expl_animations.end());
}

WorldManager::WorldManager(int screen_width, int screen_height,
	std::vector<std::unique_ptr<Object>> & v_objects, 
	std::vector< std::unique_ptr<Animation> > & v_explosions,
	std::shared_ptr<KeyboardHandling> keyboard)
	: objects{ v_objects }, 
	expl_animations{ v_explosions },
	_keyboard { keyboard }
{

	_world = std::make_unique<b2World>(b2Vec2{ 0.f, 0.f });
	_generator = std::make_unique<AsteroidGenerator>(_world, screen_width, screen_height);
	PlayerBuilder player_builder{ _world, sf::Vector2f(screen_width / 2, screen_height / 2) };
	player = player_builder.makePlayer(ShipType::type1, keyboard);
	std::unique_ptr<Object> ptr(player->getShip());
	objects.push_back(std::move(ptr));
	this->screen_width = screen_width;
	this->screen_height = screen_height;
}

void WorldManager::act(const float & delta)
{
	newAsteroid(delta);

	_world->Step(delta, 8, 3);

	for (auto & o : objects)
	{
		o->act(delta);
	}

	player->act(0);

	contact();

	animations(delta);

	removeAsteroid();
}



WorldManager::~WorldManager()
{
}
