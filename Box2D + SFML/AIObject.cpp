#include "stdafx.h"
#include "AIObject.h"


/**/
b2Vec2 AIObject::move(const float & delta, Decision & decision, bool set_to_body)
{
	float angle = _body->GetAngle() + decision.turn * stats.radians_p_s * delta;

	float acceleration = stats.speed / 2.f;

	auto linear_velocity = _body->GetLinearVelocity();

	float current_speed = linear_velocity.Length();

	float speed = decision.move * acceleration * delta;

	linear_velocity.x += sinf(angle) * speed;
	linear_velocity.y -= cosf(angle) * speed;

	if (linear_velocity.Length() > stats.speed)
		linear_velocity *= (stats.speed / linear_velocity.Length());

	if (set_to_body)
	{
		_body->SetTransform(_body->GetPosition(), angle);
		_body->SetLinearVelocity(linear_velocity);
	}

	return _body->GetPosition() + linear_velocity;
}


void AIObject::makeDecision(const float & delta)
{
	best_decision.reset();

	Decision decision;

	for (int move = -1; move <= 1; ++move)
	{
		for (int turn = -1; turn <= 1; ++turn)
		{
			for (int shoot = 0; shoot <= 1; ++shoot)
			{
				decision.set(move, turn, shoot == 1);
				rateDecision(delta, decision);
				decision.reset();
			}
		}
	}
}


void AIObject::rateDecision(const float & delta, Decision & decision)
{
	CoreOfAI::Position position = position_ai;
	position.update(move(delta, decision, false));

	CoreOfAI::FrontAndRear f_and_r;
	f_and_r.center = _body->GetPosition();
	f_and_r.front = this->frontOfShip();
	f_and_r.rear = this->backOfShip();
	

	float rate = core.moveToPlayer(f_and_r, position, player_position);

	rate += core.keepRotationToMovementDirection(position, f_and_r);

	std::for_each(closest_objects.begin(), closest_objects.end(), [&](auto & iter) -> void
	{
		auto body = iter.first;
		auto pos = iter.second;

		//rate += core.rateRayCast(position, body->GetFixtureList());
		rate += core.distanceAndApproaching(position, pos);

		if (decision.shoot)
			rate += core.shoot(f_and_r, body->GetFixtureList());
	});
/*
	for (auto & pair : closest_objects)
	{
		auto body = pair.first;
		auto pos = pair.second;

		rate += core.rateRayCast(position, body->GetFixtureList());
		rate += core.distanceAndApproaching(position, pos);

		if (decision.shoot)
			rate += core.shoot(f_and_r, body->GetFixtureList());
	}
	*/
	/*
	for (auto pair = closest_objects.begin(); pair != closest_objects.end();) // the same bug is in WorldManager.cpp(159)
	{
		auto body = pair->first;
		auto pos = pair->second;

		rate += core.rateRayCast(position, body->GetFixtureList());
		rate += core.distanceAndApproaching(position, pos);

		if (decision.shoot)
			rate += core.shoot(f_and_r, body->GetFixtureList());

		++pair;
	}
	*/
	// but here ^ I'm not sure what makes this bug
	
	decision.rate = rate;
	
	if (best_decision.rate < decision.rate || best_decision.uninitialized)
		best_decision = decision;
		
}


AIObject::AIObject(b2Body * body, sf::Shape * shape, Statistics statistics, std::map<b2Body *, Object *> & objects_map)
	: ArmedObject(body, shape, statistics),
	objects(objects_map),
	core(CoreOfAI{})
{

}


void AIObject::update(const float & delta)
{
	++frames;

	position_ai.update(_body->GetPosition());
	player_position.update(player_body->GetPosition());

	auto & objects_ref = objects;



	for (auto iter = closest_objects.begin(); iter != closest_objects.end();)
	{
		auto key = iter->first;		

		if (objects.count(key))
			++iter;
		else
			iter = closest_objects.erase(iter);
	}
	
	/*
	auto new_end = std::remove_if(closest_objects.begin(), closest_objects.end(),
		[&](auto & object) -> bool
		{
			auto key = object->first;

			return objects_ref.count(key);
		}
	);

	closest_objects.erase(new_end, closest_objects.end());

	*/
	
	if (frames >= max_frames)
	{
		frames = 0;

		for (auto pair : objects)
		{
			auto key = pair.first;
			auto object = pair.second;

			if (!core.isInRadius(this->getB2position(), object->getB2position()))
				closest_objects.erase(key);
			else
				closest_objects[key].update(object->getB2position());
		}

		closest_objects.erase(player_body);

		makeDecision(delta);

		//best_decision.print(0.f);
	}

	move(delta, best_decision, true);

	if (best_decision.shoot)
	{
		current_type = best_decision.type;
		fire();
	}
}


void AIObject::setTarget(b2Body * target)
{
	player_body = target;
	player_position = CoreOfAI::Position(player_body->GetPosition());
}


AIObject::~AIObject()
{
}
/**/