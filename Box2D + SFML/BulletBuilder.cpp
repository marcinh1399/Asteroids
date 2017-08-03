#include "stdafx.h"
#include "BulletBuilder.h"




void BulletBuilder::setPosition()
{
	world_position = _player->getBody()->GetPosition();
	screen_position = _player->getPosition();
}


b2Body * BulletBuilder::setBody(sf::Shape * _shape)
{
	b2BodyDef body_def;
	body_def.position = world_position;
	body_def.type = b2_dynamicBody;

	b2Body * _body = _world->CreateBody(&body_def);
	
	b2Vec2 * vertices = new b2Vec2[_shape->getPointCount()];

	for (int i = 0; i < _shape->getPointCount(); ++i)
	{
		vertices[i] = Coords::translate(_shape->getPoint(i));
	}

	b2PolygonShape b2_shape;
	b2_shape.Set(vertices, _shape->getPointCount());

	delete[] vertices;

	b2FixtureDef fixture_def;
	fixture_def.shape = &b2_shape;
	fixture_def.density = density;
	fixture_def.friction = friction;
	fixture_def.restitution = restitution;
	// ???
	fixture_def.filter.groupIndex = group_of_player_body;
	// ???

	_body -> CreateFixture(&fixture_def);

	return _body;
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
	float alpha = _player->getBody()->GetAngle();
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
	
	Bullet * _bullet = new Bullet(screen_position, _shape, _body);
	_body->SetUserData(_bullet);

	return _bullet;
}

Bullet * BulletBuilder::makeRocket()
{
	setPosition();
	sf::ConvexShape * _shape = new sf::ConvexShape(*_shapes->getRocketShape());
	b2Body * _body = setBody(_shape);
	_body->SetBullet(true);
	_body->SetFixedRotation(_player->getBody()->GetAngle());
	_body->SetLinearVelocity(getSpeed(speed_of_rocket));

	Bullet * _rocket = new Bullet(screen_position, _shape, _body);
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

	Bullet * _obstacle = new Bullet(screen_position, _shape, _body);
	_body->SetUserData(_obstacle);

	return _obstacle;
}

BulletBuilder::~BulletBuilder()
{
	delete _shapes;
}
