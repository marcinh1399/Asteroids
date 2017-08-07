#include "stdafx.h"
#include "BulletBuilder.h"



void BulletBuilder::setPosition()
{
	world_position = _player->getPositionWorld();
	screen_position = _player->getPositionScreen();
}


b2Body * BulletBuilder::setCircleBody(sf::CircleShape * _shape)
{
	b2BodyDef body_def;
	body_def.position = world_position;
	body_def.type = b2_dynamicBody;

	b2Body * _body = _world->CreateBody(&body_def);

	b2CircleShape b2_shape;
	b2_shape.m_radius = Coords::lengthToWorld(_shape->getRadius());

	b2FixtureDef fixture_def;
	fixture_def.shape = &b2_shape;
	fixture_def.density = density;
	fixture_def.friction = friction;
	fixture_def.restitution = restitution;

	// ???
	fixture_def.filter.groupIndex = group_of_player_body;
	// ???

	_body->CreateFixture(&fixture_def);

	return _body;
}

b2Vec2 BulletBuilder::getSpeed(const float & speed)
{
	float alpha = _player->getAngle();
	float x = cos(alpha) * speed;
	float y = sin(alpha) * speed;

	return b2Vec2{ x, y };
}

BulletBuilder::BulletBuilder(Player * ptr_player, std::unique_ptr<b2World>& u_world)
	: _player{ptr_player}, _world{u_world}
{
	/////////////////////////////////////
}

Bullet * BulletBuilder::makeBullet()
{
	setPosition();
	sf::CircleShape * _shape = new sf::CircleShape(*_shapes->getBulletShape());
	b2Body * _body = setCircleBody(_shape);
	_body->SetBullet(true);
	_body->SetLinearVelocity(getSpeed(speed_of_bullet));
	
	float hp = 1.f;
	float dmg = _body->GetMass() * 2.f;

	Bullet * _bullet = new Bullet(hp, _body, _shape, dmg);
	_body->SetUserData(_bullet);

	return _bullet;
}

Bullet * BulletBuilder::makeRocket()
{
	setPosition();
	sf::ConvexShape * _shape = new sf::ConvexShape(*_shapes->getRocketShape());
	b2Body * _body = setBody(_shape);
	_body->SetBullet(true);
	_body->SetFixedRotation(_player->getAngle());
	_body->SetLinearVelocity(getSpeed(speed_of_rocket));

	float hp = 1.f;
	float dmg = _body->GetMass() * 10.f;

	Bullet * _rocket = new Bullet(hp, _body, _shape, dmg);
	_body->SetUserData(_rocket);

	return _rocket;
}

Bullet * BulletBuilder::makeObstacle()
{
	setPosition();
	sf::RectangleShape * _shape = new sf::RectangleShape(*_shapes->getObstacleShape());
	b2Body * _body = setBody(_shape);
	// propably I will add velocity for obstacle,
	// it will be rescaled vector of player's speed.

	float hp = _body->GetMass() * 10.f;
	float dmg = _body->GetMass() * 20.f;

	Bullet * _obstacle = new Bullet(hp, _body, _shape, dmg);
	_body->SetUserData(_obstacle);

	return _obstacle;
}

BulletBuilder::~BulletBuilder()
{
	delete _shapes;
}
