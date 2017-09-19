#include "stdafx.h"
#include "ArmedObject.h"




ArmedObject::~ArmedObject()
{
}

void ArmedObject::fire()
{
	if (weapon_managers[current_type]->fire())
	{
		missile.set(current_type, stats.bullet_dmg);
		notifyObservers();
	}
}

void ArmedObject::setManager(Bullet::Type type)
{
	current_type = type;
}

void ArmedObject::updateMissileManager(const float & delta)
{
	for (auto pair : weapon_managers)
		pair.second->update(delta);
}

ArmedObject::ArmedObject(b2Body * body, sf::Shape * shape, Statistics statistics)
	: Object(body, shape),
	stats(statistics)
{

}

void ArmedObject::initManagers(const ManagerInit & bullet, const ManagerInit & rocket, const ManagerInit & obstacle)
{
	current_type = Bullet::Type::bullet;

	weapon_managers[Bullet::Type::bullet] = new WeaponManager(bullet);
	weapon_managers[Bullet::Type::rocket] = new WeaponManager(rocket);
	weapon_managers[Bullet::Type::obstacle] = new WeaponManager(obstacle);

	for (auto pair : weapon_managers)
		pair.second->updateCooldown(stats.bullet_cdwn);
}

void ArmedObject::addMissiles(Bullet::Type type, size_t quantity)
{
	weapon_managers[type]->addAmountOfBullets(quantity);
}

const ArmedObject::Missile ArmedObject::getMissile()
{
	Missile copy = missile;

	missile.reset();

	return copy;
}

b2Vec2 ArmedObject::frontOfShip()
{
	auto transform = getShape()->getTransform();
	auto point_pos = transform.transformPoint(getShape()->getPoint(0));

	return Coords::translate(point_pos);
}

b2Vec2 ArmedObject::backOfShip()
{
	auto transform = getShape()->getTransform();
	auto point_pos = transform.transformPoint(getShape()->getPoint(2));

	return Coords::translate(point_pos);
}
