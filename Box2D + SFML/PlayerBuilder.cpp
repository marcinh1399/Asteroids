#include "stdafx.h"
#include "PlayerBuilder.h"




b2Body * PlayerBuilder::makeBody(sf::Shape * _shape)
{
	b2BodyDef body_def;
	body_def.position = Coords::translate(position);
	body_def.type = b2_dynamicBody;

	b2Body * _body = _world->CreateBody(&body_def);

	b2PolygonShape shape = Coords::translateShape(_shape);

	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;
	fixture_def.density = density;
	fixture_def.friction = friction;
	fixture_def.restitution = 0.5;
	

	// ???
	fixture_def.filter.groupIndex = 0;
	// ???

	_body->CreateFixture(&fixture_def);

	return _body;
}

PlayerBuilder::PlayerBuilder(std::unique_ptr<b2World>& world, sf::Vector2f pos)
	: _world{ world }, position{ pos }
{

}

std::unique_ptr<Player> PlayerBuilder::makePlayer(ShipType type, std::shared_ptr<KeyboardHandling> keyboard)
{
	auto pair = types.getType(type);
	sf::Shape * _s = pair.first;
	Statistics st = pair.second;
	b2Body * _b = makeBody(_s);
	float hp = _b->GetMass() * hp_multipier;
	float dmg = hp; // ????
	Spaceship * ship = new Spaceship(hp, _b, _s, dmg, st);

	return std::make_unique<Player>(ship, keyboard);
}


PlayerBuilder::~PlayerBuilder()
{
}
