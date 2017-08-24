#include "stdafx.h"
#include "Factory.h"



b2Body * Factory::makeBody(const BodyDescription & desc, bool group)
{
	b2BodyDef body_def;
	body_def.position = desc.position;
	body_def.type = desc.type;

	b2Body * _body = _world->CreateBody(&body_def);

	b2FixtureDef fixture_def;
	fixture_def.shape = desc.shape;
	fixture_def.density = desc.density;
	fixture_def.friction = desc.friction;
	fixture_def.restitution = desc.restitution;

	if (group)
	{
		fixture_def.filter.groupIndex = -1;
	}

	_body->CreateFixture(&fixture_def);
	_body->SetLinearVelocity(desc.linear_velocity);
	_body->SetAngularVelocity(desc.angular_velocity);

	return _body;
}

Factory::Factory(std::unique_ptr<b2World> & world, sf::Vector2f world_bnds)
	: _world(world),
	world_bounds(world_bnds)
{
	asteroid_generator = std::make_unique<AsteroidGenerator>(world_bnds.x, world_bnds.y);
	spaceship_types = SpaceshipTypes::getInstance();
}

std::unique_ptr<Asteroid> Factory::makeAsteroid()
{	
	auto sf_shape = asteroid_generator->makeShape();
	auto sf_pos = asteroid_generator->getPosition();
	auto ptr_shape = Coords::translateShape(sf_shape);
	

	BodyDescription description;
	description.position = Coords::translate(sf_pos);
	description.type = b2BodyType::b2_dynamicBody;
	description.shape = ptr_shape.get();
	description.density = asteroid_generator->getDensity();
	description.friction = asteroid_generator->getFriction();
	description.restitution = asteroid_generator->getRestitution();
	description.linear_velocity = asteroid_generator->getLinearVelocity(sf_pos);
	description.angular_velocity = asteroid_generator->getAngularVelocity();

	auto body = makeBody(description, false);

	sf_shape->setPosition(sf_pos);

	printf("Mass = %f.6\n", body->GetMass());

	return std::make_unique<Asteroid>(body, sf_shape);
}

std::shared_ptr<Player> Factory::makePlayer(std::unique_ptr<Spaceship> & ship, 
	std::shared_ptr<KeyboardHandling> keyboard)
{
	_player = std::make_shared<Player>(ship.get());

	return _player;
}

std::unique_ptr<Spaceship> Factory::makeSpaceship(sf::Vector2f sf_pos, 
	SpaceshipTypes::ShipType type, std::shared_ptr<KeyboardHandling> keyboard)
{
	auto ship = spaceship_types->getType(type);
	auto sf_shape = new sf::ConvexShape(ship->getShape());
	auto stats = ship->getCurrentStats();
	auto ptr_shape = Coords::translateShape(sf_shape);

	BodyDescription description;
	description.position = Coords::translate(sf_pos);
	description.type = b2BodyType::b2_kinematicBody;
	description.shape = ptr_shape.get();
	description.density = 15.f;
	description.friction = 0.6f;
	description.restitution = 0.5f;
	description.linear_velocity = b2Vec2(0.f, 0.f);
	description.angular_velocity = 0.f;

	auto body = makeBody(description, true);

	sf_shape->setPosition(sf_pos);

	return std::make_unique<Spaceship>(body, sf_shape, stats, keyboard);
}

std::unique_ptr<Bullet> Factory::makeBullet(Bullet::Type type)
{
	auto sf_pos = _player->getPositionScreen();
	auto sf_shape = bullet_shapes.getShape(type);
	float alpha = _player->getAngle();
	float speed = bullet_shapes.getSpeed(type);
	float hp = bullet_shapes.getHP(type);
	auto ptr_shape = Coords::translateShape(sf_shape);

	
	auto transform = _player->getShape()->getTransform();
	auto point_pos = transform.transformPoint(_player->getShape()->getPoint(0));

	BodyDescription description;
	description.position = Coords::translate(point_pos);
	//(sf_pos);
	description.type = b2BodyType::b2_dynamicBody;
	description.shape = ptr_shape.get();
	description.density = 30.f;
	description.friction = 0.7f;
	description.restitution = 0.3f;
	description.linear_velocity = b2Vec2(sin(alpha) * speed, -cos(alpha) * speed);
	description.angular_velocity = 0.f;

	auto body = makeBody(description, true);

	body->SetTransform(body->GetPosition(), alpha);
	body->SetBullet(true);

	sf_shape->setPosition(sf_pos);

	return std::make_unique<Bullet>(body, sf_shape, hp);
}

std::unique_ptr<Enemy> Factory::makeEnemy(std::shared_ptr<GameObjects> g_objects)
{
	auto ship = spaceship_types->getType(SpaceshipTypes::ShipType::type1);
	auto sf_shape = new sf::ConvexShape(ship->getShape());
	auto stats = ship->getCurrentStats();
	auto ptr_shape = Coords::translateShape(sf_shape);
	auto sf_pos = asteroid_generator->getPosition();

	sf_shape->setOutlineColor(sf::Color::Red);

	BodyDescription description;
	description.position = Coords::translate(sf_pos);
	description.type = b2BodyType::b2_kinematicBody;
	description.shape = ptr_shape.get();
	description.density = 15.f;
	description.friction = 0.6f;
	description.restitution = 0.5f;
	description.linear_velocity = b2Vec2(0.f, 0.f);
	description.angular_velocity = 0.f;

	auto body = makeBody(description, true);

	sf_shape->setPosition(sf_pos);


	return std::make_unique<Enemy>(body, sf_shape, stats, g_objects);
}










std::unique_ptr<Bullet> Factory::makeBullet(Bullet::Type type, Enemy * object)
{
	auto sf_pos = Coords::translate(object->getBody()->GetPosition());
	auto sf_shape = bullet_shapes.getShape(type);
	float alpha = object->getBody()->GetAngle();
	float speed = bullet_shapes.getSpeed(type);
	float hp = bullet_shapes.getHP(type);
	auto ptr_shape = Coords::translateShape(sf_shape);


	auto transform = object->getShape()->getTransform();
	auto point_pos = transform.transformPoint(object->getShape()->getPoint(0));

	BodyDescription description;
	description.position = Coords::translate(point_pos);
	//(sf_pos);
	description.type = b2BodyType::b2_dynamicBody;
	description.shape = ptr_shape.get();
	description.density = 30.f;
	description.friction = 0.7f;
	description.restitution = 0.3f;
	description.linear_velocity = b2Vec2(sin(alpha) * speed, -cos(alpha) * speed);
	description.angular_velocity = 0.f;

	auto body = makeBody(description, true);

	body->SetTransform(body->GetPosition(), alpha);
	body->SetBullet(true);

	sf_shape->setPosition(sf_pos);

	return std::make_unique<Bullet>(body, sf_shape, hp);
}







Factory::~Factory()
{
}
