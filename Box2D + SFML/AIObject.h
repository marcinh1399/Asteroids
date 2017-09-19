#pragma once
#include "ArmedObject.h"
#include "CoreOfAI.h"

class CoreOfAI;

class AIObject :
	public ArmedObject
{

private:

	size_t max_frames = 6;
	size_t frames = max_frames;


	struct Decision
	{
		bool uninitialized;
		float rate;
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
			uninitialized = true;
			rate = 0.f;
			move = 0;
			turn = 0;
			shoot = false;
			type = Bullet::Type::bullet;
		}

		void set(int move, int turn, bool shoot)
		{
			this->uninitialized = false;
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


	std::map<b2Body *, Object *> & objects;

	/**/
	std::map<b2Body *, CoreOfAI::Position> closest_objects;

	b2Body * player_body;

	CoreOfAI::Position player_position;

	Decision best_decision;

	CoreOfAI core;

	CoreOfAI::Position position_ai;

	Decision decision;


	b2Vec2 move(const float & delta, Decision & decision, bool set_to_body);


	void makeDecision(const float & delta);


	void rateDecision(const float & delta, Decision & decision);

	/**/

public:


	AIObject(b2Body * body, sf::Shape * shape, Statistics statistics, std::map<b2Body *, Object *> & objects_map);


	void update(const float & delta);


	void setTarget(b2Body * target);

	virtual ~AIObject();
};

