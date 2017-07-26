#include "stdafx.h"
#include "AsteroidBuilder.h"



void AsteroidBuilder::setRangeOfRadius(const int & max_radius)
{
	min_radius = rnd_radius = max_radius / 2;
}

AsteroidBuilder::AsteroidBuilder(int max_radius, float scale, std::unique_ptr<b2World> & unique_world) : _world(unique_world)
{
	setRangeOfRadius(max_radius);
	this->scale = scale;
}

AsteroidBuilder::~AsteroidBuilder()
{
}

AsteroidBuilder * AsteroidBuilder::setWorldPosition(b2Vec2 position)
{
	world_position = position;
	return this;
}

AsteroidBuilder * AsteroidBuilder::setScreenPosition(sf::Vector2f position)
{
	screen_position = position;
	return this;
}


AsteroidBuilder * AsteroidBuilder::setSfmlShape()
{
	amount_of_vertices = rand() % rnd_vertices + min_vertices;
	int angle_range = 360 / amount_of_vertices;

	sf_vertices = new sf::Vector2f[amount_of_vertices];


	for (int i = 0; i < amount_of_vertices; ++i)
	{
		int length = min_radius + rand() % rnd_radius;
		int angle = rand() % angle_range + i * angle_range;
		float radians = angle * M_PI / 180.f;
		float x = sinf(radians) * length;
		float y = cosf(radians) * length;

		sf_vertices[i] = sf::Vector2f{ x, y };

#ifndef NDEBUG
		Tests::isPointInCircle(x, y, min_radius + rnd_radius - 1);
#endif
	}

	_shape = new  sf::ConvexShape(amount_of_vertices);
	for (int i = 0; i < amount_of_vertices; ++i)
		_shape->setPoint(i, sf_vertices[i]);

	_shape->setFillColor(sf::Color::Transparent);
	_shape->setOutlineThickness(2);
	_shape->setOutlineColor(sf::Color::White);
	_shape->setPosition(screen_position);

	return this;
}

AsteroidBuilder * AsteroidBuilder::setBox2DShape()
{
	b2_vertices = new b2Vec2[amount_of_vertices];

	for (int i = 0; i < amount_of_vertices; ++i)
	{
		float x = sf_vertices[i].x / scale;
		float y = sf_vertices[i].y / scale;
		b2_vertices[i].Set(x, y);
	}

	return this;
}

AsteroidBuilder * AsteroidBuilder::setBody()
{
	b2BodyDef body_def;
	body_def.position = world_position;
	body_def.type = b2_dynamicBody;

	_body = _world->CreateBody(&body_def);

	b2PolygonShape shape;
	shape.Set(b2_vertices, amount_of_vertices);

	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;
	fixture_def.density = randDensity();
	fixture_def.friction = randFriction();
	fixture_def.restitution = 0.5;

	_body->CreateFixture(&fixture_def);

	return this;
}

AsteroidBuilder * AsteroidBuilder::setStamina()
{
	stamina = _body->GetMass();
	return this;
}

AsteroidBuilder * AsteroidBuilder::setLinearVelocity(b2Vec2 v)
{
	_body->SetLinearVelocity(v);
	return this;
}

AsteroidBuilder * AsteroidBuilder::setAngularVelocity(float angle)
{
	_body->SetAngularVelocity(angle);
	return this;
}

Asteroid * AsteroidBuilder::build()
{
	Asteroid * _asteroid = new Asteroid(stamina, scale, _body, _shape);
	
	
	delete[] b2_vertices;
	delete[] sf_vertices;

	return _asteroid;
}



float AsteroidBuilder::randDensity()
{
	return (rand() % RND_DENSITY + MIN_DENSITY) * SCL_DENSITY;
}

float AsteroidBuilder::randFriction()
{
	return (rand() % RND_FRICTION + MIN_FRICTION) * SCL_FRICTION;
}