#pragma once
#include "Object.h"
#include <Box2D\Box2D.h>
#include "Animation.h"
#include "ObserversController.h"
#include <map>


class Factory;


class GameObjects
{

public:

	std::map<b2Body *, Object *> objects;
	std::map<b2Body *, ObserversController *> observers;

	std::list<Animation> explosions;

	GameObjects();

	/*
	boost::ptr_map<b2Body *, Object> objects;
	boost::ptr_map<b2Body *, ObserversController> observers;
	*/

};

