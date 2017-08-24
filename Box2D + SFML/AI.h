#pragma once
#include "GameObjects.h"
#include <list>
#include <map>
#include <memory>
#include <Box2D\Box2D.h>
#include <algorithm>
#include "Bullet.h"
#include "Statistics.h"
#include <climits>
#include "Enemy.h"


class GameObjects;
class Enemy;
class Factory;


class AI
{

private:

	struct Decision 
	{
		int move;
		int turn;
		bool shoot;
		Bullet::Type type;

		Decision()
		{
			reset();
		}

		void reset()
		{
			move = 0;
			turn = 0;
			shoot = false;
			type = Bullet::Type::bullet;
		}

		void set(int move, int turn, bool shoot)
		{
			this->move = move;
			this->turn = turn;
			this->shoot = shoot;
			type = Bullet::Type::bullet;
		}


		void print(float rate) const
		{
			printf("Decision:\nmove: %d\nturn: %d\nrate: %f.6\n", move, turn, rate);
		}
	};


	constexpr static int radius = 50;
	constexpr static int squared_radius = radius * radius;

	constexpr static int close = 25;
	constexpr static int squared_close = close * close;


	constexpr static float multiplier_player = 4.f;


	b2Body * body;
	b2Body * body_player; // target

	constexpr static float squared_huge_difference = 25.f;

	


	std::map<b2Body *, float> map_of_bodies;

	std::map<b2Body *, float> closest_bodies;
	std::map<b2Body *, float> approaching_bodies;
	//                  ^ float parameter keeps difference of squared distance between updates
	//					in closest bodies second parameter keeps difference of squared distance between updates, too.	


	// first - ptr, second distance between this->body and body from map
	// if distance is growing fast then remove from map
	// if distance is decreasing then add to list of upcoming bodies
	// if body is very close then check angle and try to destroy it by weapons
	// always try to get closer to player if it is possible,
	// try to avoid asteroids as much as possible
	/* each proposition of move is rated by algorithm, 
	moves which approaching to player are better rated, 
	they are multiplying by const value
	*/




	Statistics stats_of_ship;
	float radius_of_ship;


	Enemy * object;




	std::shared_ptr<GameObjects> game_objects;

	//std::list<b2Body *> bodies;

	std::unique_ptr<Factory> & factory;

	std::vector<std::unique_ptr<Object>> & objects;

	std::unique_ptr<b2World> & world;

	std::vector<std::pair<Decision, float>> decisions;


	Decision current_decision;


	void update(const float & delta);


	void closest(const float & delta);


	void makeDecision(const float & delta);


	void rateDecision(const float & delta, const Decision & decision);


	b2Vec2 nextPosition(const float & delta, const Decision & decision);

	b2Vec2 linearVelocity(const float & delta, const Decision & decision);
	
	
	float rateShot(b2Body * body_from_world);


public:

	AI(std::shared_ptr<GameObjects> g_objects, Enemy * object);

	void act(const float & delta);

	~AI();
};

