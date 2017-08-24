#include "stdafx.h"
#include "AI.h"


void AI::update(const float & delta)
{

	int i = 0;

	auto body_from_world = world->GetBodyList();

	while (body_from_world)
	{


		float squared_distance = b2DistanceSquared(body->GetPosition(), body_from_world->GetPosition());

		if (map_of_bodies.count(body_from_world))
		{
			float delta_dist = squared_distance - map_of_bodies[body_from_world];

			if (delta_dist >= squared_huge_difference || squared_distance > squared_radius) 
			{
				map_of_bodies.erase(body_from_world);
				approaching_bodies.erase(body_from_world);
				closest_bodies.erase(body_from_world);
			}
			else
			{
				map_of_bodies[body_from_world] = squared_distance;

				if (delta_dist < 0.f)
					approaching_bodies[body_from_world] = delta_dist;
				else
					approaching_bodies.erase(body_from_world);

				if (squared_distance <= squared_close)
					closest_bodies[body_from_world] = delta_dist;
				else
					closest_bodies.erase(body_from_world);
					
			}
		}
		else
		{
			if (squared_distance <= squared_radius)
				map_of_bodies[body_from_world] = squared_distance;
		}

		body_from_world = body_from_world->GetNext();
	}
	
	map_of_bodies.erase(body_player);
	approaching_bodies.erase(body_player);
	closest_bodies.erase(body_player);
	map_of_bodies.erase(body);
	approaching_bodies.erase(body);
	closest_bodies.erase(body);

}



void AI::rateDecision(const float & delta, const Decision & decision)
{
	b2Vec2 next_position = nextPosition(delta, decision);
	auto v2 = linearVelocity(delta, decision);
	auto v1 = body_player->GetPosition() - next_position;
	//auto v2 = Coords::translate(vec);


/*
	float w = v1.x * v2.x + v1.y + v2.y;
	float n = v1.Length() * v2.Length();
*/

	float rate = 0;




	rate -= (b2Abs(atan2(v1.y, v1.x) - atan2(v2.y, v2.x)));
	rate += 50 * v2.LengthSquared();



	for (auto body_from_world : closest_bodies)
	{
		auto _body = body_from_world.first;

		float radius = static_cast<Object *>(_body->GetUserData())->getRadius();
	

		auto prev_squared_distance = b2DistanceSquared(_body->GetPosition(), body->GetPosition());
		auto next_squared_distance = b2DistanceSquared(_body->GetPosition(), next_position);


		auto transform = static_cast<Object *>(body->GetUserData())->getShape()->getTransform();
		auto point_pos1 = transform.transformPoint(static_cast<Object *>(body->GetUserData())->getShape()->getPoint(0));
		auto point_pos2 = transform.transformPoint(static_cast<Object *>(body->GetUserData())->getShape()->getPoint(2));

		auto vec = point_pos1 - point_pos2;
		
		//auto v1 = body_player->GetPosition() - body->GetPosition();
		//auto v2 = Coords::translate(vec);


		


		//float w = v1.x * v2.x + v1.y + v2.y;
		//float n = v1.Length() * v2.Length();




		
		auto current_rate = (next_squared_distance - prev_squared_distance) * (squared_radius - next_squared_distance);


		if (decision.shoot)
			current_rate += rateShot(body_from_world.first);
		
		

		auto squared_radii = (radius + radius_of_ship) * (radius + radius_of_ship);

		if (squared_radii >= next_squared_distance && current_rate < 0)
			current_rate = -100000;

		rate += current_rate;
	}

	auto prev_squared_distance_player = b2DistanceSquared(body_player->GetPosition(), body->GetPosition());
	auto next_squared_distance_player = b2DistanceSquared(body_player->GetPosition(), next_position);

	rate += 30 * multiplier_player * (prev_squared_distance_player - next_squared_distance_player);
	
	if (decision.shoot)
		rate += 10 * rateShot(body_player);

	decisions.push_back(std::pair<Decision, float>(decision, rate));
}

b2Vec2 AI::nextPosition(const float & delta, const Decision & decision)
{

	float alpha = body->GetAngle();

	float angle = alpha + (decision.turn * delta * stats_of_ship.radians_p_s);


	float current_speed = body->GetLinearVelocity().Length();
	float acceleration = stats_of_ship.speed / 2.f;



	b2Vec2 vel(body->GetLinearVelocity());
	float s = decision.move  *  delta  *   acceleration;
	vel.x = sin(angle) * s;
	vel.y = -cos(angle) * s;

	
	if (vel.Length() > stats_of_ship.speed)
		vel *= (stats_of_ship.speed / vel.Length());


	float current_speed_angular = body->GetAngularVelocity();
	float acceleration_angular = stats_of_ship.radians_p_s / 1.5f;

	current_speed_angular += acceleration_angular * decision.turn * delta;

	if (current_speed_angular > stats_of_ship.radians_p_s)
		current_speed_angular = stats_of_ship.radians_p_s;


	return body->GetPosition() + vel;
}

b2Vec2 AI::linearVelocity(const float & delta, const Decision & decision)
{

	float alpha = body->GetAngle();

	float angle = alpha + (decision.turn * delta * stats_of_ship.radians_p_s);


	float current_speed = body->GetLinearVelocity().Length();
	float acceleration = stats_of_ship.speed / 2.f;



	b2Vec2 vel(body->GetLinearVelocity());
	float s = decision.move  *  delta  *   acceleration;
	vel.x = sin(angle) * s;
	vel.y = -cos(angle) * s;


	if (vel.Length() > stats_of_ship.speed)
		vel *= (stats_of_ship.speed / vel.Length());


	float current_speed_angular = body->GetAngularVelocity();
	float acceleration_angular = stats_of_ship.radians_p_s / 1.5f;

	current_speed_angular += acceleration_angular * decision.turn * delta;

	if (current_speed_angular > stats_of_ship.radians_p_s)
		current_speed_angular = stats_of_ship.radians_p_s;


	return vel;
	
}

float AI::rateShot(b2Body * body_from_world)
{
	
	b2RayCastInput ray_cast_input;
	ray_cast_input.p1 = object->backOfShip();
	ray_cast_input.p2 = object->frontOfShip();
	ray_cast_input.maxFraction = 25;

	b2RayCastOutput ray_cast_output;
	
	float rate = 0;

	auto fixture = body_from_world->GetFixtureList();  // only one fixture


	if (fixture->RayCast(&ray_cast_output, ray_cast_input, 0))
	{
		rate = (ray_cast_input.maxFraction - ray_cast_output.fraction) * 100;
	}

	return rate;
}



void AI::closest(const float & delta)
{
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



void AI::makeDecision(const float & delta)
{
	

	closest(delta);

	std::pair<Decision, float> best = decisions.front();

	for (auto pair : decisions)
	{
		if (pair.second > best.second)
			best = pair;

		//pair.first.print(pair.second);
	}

	current_decision = best.first;


	current_decision.print(best.second);
}








AI::AI(std::shared_ptr<GameObjects> g_objects, Enemy * object)
	: world(g_objects->world),
	factory(g_objects->factory),
	objects(g_objects->objects),
	game_objects(g_objects)
{
	body_player = g_objects->player->getBody();
	this->object = object;
	body = object->getBody();
	stats_of_ship = object->getStats();
	radius_of_ship = object->getRadius();
}


void AI::act(const float & delta)
{
	update(delta);

	makeDecision(delta);

	float alpha = body->GetAngle();

	float angle = alpha + current_decision.turn * delta  * stats_of_ship.radians_p_s;


	body->SetTransform(body->GetPosition(), angle);

	
	

	float current_speed = body->GetLinearVelocity().Length();
	float acceleration = stats_of_ship.speed / 2.f;





	b2Vec2 vel(body->GetLinearVelocity());
	float s = current_decision.move * delta * acceleration;
	vel.x += sin(angle) * s;
	vel.y -= cos(angle) * s;
	
	if (vel.Length() > stats_of_ship.speed)
		vel *= (stats_of_ship.speed / vel.Length());
	
	body->SetLinearVelocity(vel);

	if (current_decision.shoot)
	{
		game_objects->enemy_bullet = factory->makeBullet(current_decision.type, object);
	}

	decisions.clear();
	current_decision.reset();
}


AI::~AI()
{
}
