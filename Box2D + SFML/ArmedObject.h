#pragma once
#include "Object.h"
#include <map>
#include "WeaponManager.h"
#include "Statistics.h"

class WeaponManager;

struct ManagerInit
{
	float cooldown_in_seconds;
	size_t init_amount_of_bullets;
	size_t max_value;

	void unavailable()
	{
		cooldown_in_seconds = INFINITY;
		init_amount_of_bullets = 0;
		max_value = 0;
	}
};

class ArmedObject :
	public Object
{
public:

	


	struct Missile
	{
		bool fire;
		float dmg_multiplier;
		Bullet::Type type_of_missile;

		void reset()
		{
			fire = false;
			dmg_multiplier = 1.f;
		}

		void set(Bullet::Type type, float damage_multiplier)
		{
			fire = true;
			dmg_multiplier = damage_multiplier;
			type_of_missile = type;
		}
	};


	Missile missile;


protected:

	Bullet::Type current_type;
	std::map<Bullet::Type, WeaponManager *> weapon_managers;


	Statistics stats;


	void fire();


	void setManager(Bullet::Type type);


	void updateMissileManager(const float & delta);


public:

	ArmedObject(b2Body * body, sf::Shape * shape, Statistics statistics);

	void initManagers(const ManagerInit & bullet, const ManagerInit & rocket, const ManagerInit & obstacle);

	void addMissiles(Bullet::Type type, size_t quantity);

	const Missile getMissile();

	b2Vec2 frontOfShip();

	b2Vec2 backOfShip();

	virtual ~ArmedObject();
};
