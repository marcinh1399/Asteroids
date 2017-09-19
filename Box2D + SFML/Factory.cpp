#include "stdafx.h"
#include "Factory.h"



b2Body * Factory::makeBody(const BodyDescription & desc, bool group)
{
	b2BodyDef body_def;
	body_def.position = desc.position;
	body_def.type = desc.type;

	b2Body * _body = b2world.CreateBody(&body_def);

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


Factory::Factory(b2World & world, GameObjects & game_objects)
	: b2world(world),
	objects(game_objects)
{
	spaceship_types = SpaceshipTypes::getInstance();
}


/*

Factory::Factory(std::shared_ptr<b2World> world, ObjectsMap map)
	: objects(map)
{
	b2world = world;
	spaceship_types = SpaceshipTypes::getInstance();
}

*/

Asteroid * Factory::makeAsteroid()
{	
	auto sf_shape = asteroid_generator.makeShape();
	auto sf_pos = asteroid_generator.getSFposition();
	auto ptr_shape = Coords::translateShape(sf_shape);
	

	BodyDescription description;
	description.position = Coords::translate(sf_pos);
	description.type = b2BodyType::b2_dynamicBody;
	description.shape = ptr_shape.get();
	description.density = asteroid_generator.getDensity();
	description.friction = asteroid_generator.getFriction();
	description.restitution = asteroid_generator.getRestitution();
	description.linear_velocity = asteroid_generator.getLinearVelocity(sf_pos);
	description.angular_velocity = asteroid_generator.getAngularVelocity();

	auto body = makeBody(description, false);

	sf_shape->setPosition(sf_pos);

	//printf("Mass = %f\n", body->GetMass());

	return new Asteroid(body, sf_shape);
}

/*
std::shared_ptr<Player> Factory::makePlayer(std::unique_ptr<Spaceship> & ship, 
	std::shared_ptr<KeyboardHandling> keyboard)
{
	_player = std::make_shared<Player>(ship.get());

	return _player;
}

Spaceship * Factory::makeSpaceship(sf::Vector2f sf_pos, 
	SpaceshipTypes::ShipType type, Keyboard keyboard)
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

	return new Spaceship(body, sf_shape, stats, keyboard);
}
*/

PlayerObject * Factory::makePlayer(sf::Vector2f sf_pos, Keyboard keyboard, SpaceshipTypes::ShipType type)
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

	
	ManagerInit bullet{ 1 / 15.f, 100, 500 };
	ManagerInit rocket{ 1.f, 10, 50 };
	ManagerInit obstacle{ 50.f, 1, 5 };
	
	auto player = new PlayerObject(body, sf_shape, stats, keyboard);

	player->initManagers(bullet, rocket, obstacle);

	return player;
}



EnemyAI * Factory::makeEnemy()
{
	auto ship = spaceship_types->getType(SpaceshipTypes::ShipType::type1);
	auto sf_shape = new sf::ConvexShape(ship->getShape());
	auto stats = ship->getCurrentStats();
	auto ptr_shape = Coords::translateShape(sf_shape);
	auto sf_pos = asteroid_generator.getSFposition();

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

	auto enemy = new EnemyAI(body, sf_shape, stats, objects.objects);

	ManagerInit bullet_init;
	bullet_init.cooldown_in_seconds = 1.f / 10.f;
	bullet_init.init_amount_of_bullets = 100;
	bullet_init.max_value = 500;

	ManagerInit rocket_init;
	rocket_init.unavailable();

	ManagerInit obstacle_init;
	obstacle_init.unavailable();

	enemy->initManagers(bullet_init, rocket_init, obstacle_init);

	return enemy;
}



Bullet * Factory::makeBullet(Bullet::Type type, ArmedObject * object, float multiplier)
{

	auto v = object->frontOfShip() - object->backOfShip();

	auto sf_pos = Coords::translate(object->frontOfShip() + 2 * v);
	auto sf_shape = bullet_shapes.getShape(type);
	float alpha = object->getBody()->GetAngle();
	float speed = bullet_shapes.getSpeed(type);
	float hp = bullet_shapes.getHP(type) * multiplier;
	auto ptr_shape = Coords::translateShape(sf_shape);

	/*
	auto transform = object->getShape()->getTransform();
	auto point_pos = transform.transformPoint(object->getShape()->getPoint(0));
	*/

	BodyDescription description;
	description.position = Coords::translate(sf_pos);
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

	return new Bullet(body, sf_shape, hp);
}




Factory::~Factory()
{
}
