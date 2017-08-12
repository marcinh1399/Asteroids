#pragma once
#include "IListener.h"
#include <memory>
#include "WeaponManager.h"
#include "Factory.h"
#include "GameObjects.h"



class BulletHandling :
	public IListener
{

private:

	std::vector< std::unique_ptr<Object> > & objects;
	std::unique_ptr<Factory> & _factory;

	WeaponManager bullet_manager;
	WeaponManager rocket_manager;
	WeaponManager obstacle_manager;

	WeaponManager * current_manager;
	Bullet::Type current_type;


public:


	BulletHandling(std::shared_ptr<GameObjects> objects);




	~BulletHandling();

	void update(const float & delta);

	// Inherited via IListener
	virtual void handling(const float & delta) override;
};

