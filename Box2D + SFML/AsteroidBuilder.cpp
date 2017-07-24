#include "stdafx.h"
#include "AsteroidBuilder.h"



void AsteroidBuilder::setRangeOfRadius(const int & max_radius)
{
	min_radius = rnd_radius = max_radius / 2;
}

int AsteroidBuilder::generateShape()
{
	int amount_of_vertices = rand() % rnd_vertices + min_vertices;
	int angle_range = 360 / amount_of_vertices;

	b2_vertices = new b2Vec2[amount_of_vertices];
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

		float omega = 0.01f;
		float xxyy = x*x + y*y;
		float max_length = (min_radius + rnd_radius - 1)*(min_radius + rnd_radius - 1) + omega;

		#endif // !NDEBUG

		assert(xxyy <= max_length);

	}

	resizeToB2(amount_of_vertices);

	return amount_of_vertices;
}

Asteroid * AsteroidBuilder::getNewAsteroid(const float & xWorld, const float & yWorld)
{
	int amount_of_vertices = generateShape();
	b2Body * _body = generateBody(xWorld, yWorld, amount_of_vertices);
	sf::ConvexShape * _shape = generateSFShape(amount_of_vertices);
	Asteroid * _asteroid = new Asteroid(_body, _shape);
	_body->SetUserData(_asteroid);
	delete[] b2_vertices;
	delete[] sf_vertices;
	return _asteroid;
}

b2Body * AsteroidBuilder::generateBody(const float & x, const float & y, const int & amount)
{

	b2BodyDef * _body_def = new b2BodyDef();
	_body_def->position.Set(x, y);
	_body_def->type = b2_dynamicBody;

	b2Body * _body = _world->CreateBody(_body_def);

	b2PolygonShape * _shape = new b2PolygonShape();
	_shape->Set(b2_vertices, amount);

	b2FixtureDef * _fixture_def = new b2FixtureDef();
	_fixture_def->shape = _shape;
	_fixture_def->density = randDensity();
	_fixture_def->friction = randFriction();
	_fixture_def->restitution = 0.5; //////////////////////////////

	_body->CreateFixture(_fixture_def);
	_body->SetLinearVelocity(b2Vec2{ -10.f, -20.f }); // only for tests

	return _body;
}

sf::ConvexShape * AsteroidBuilder::generateSFShape(const int & amount)
{
	sf::ConvexShape * _shape = new sf::ConvexShape();
	_shape->setPointCount(amount);
	
	for (int i = 0; i < amount; ++i)
		_shape->setPoint(i, sf_vertices[i]);

	_shape->setOrigin(0, 0);
	_shape->setOutlineThickness(2);
	_shape->setOutlineColor(sf::Color::Green);
	_shape->setFillColor(sf::Color::White);

	return _shape;
}

void AsteroidBuilder::resizeToB2(int amount)
{
	for (int i = 0; i < amount; ++i)
	{
		float x = sf_vertices[i].x * SCALE;
		float y = sf_vertices[i].y * SCALE;
		b2_vertices[i].Set(x, y);
	}
}

float AsteroidBuilder::randDensity()
{
	return (rand() % RND_DENSITY + MIN_DENSITY) * SCL_DENSITY;
}

float AsteroidBuilder::randFriction()
{
	return (rand() % RND_FRICTION + MIN_FRICTION) * SCL_FRICTION;
}


AsteroidBuilder::AsteroidBuilder(int max_radius, std::unique_ptr<b2World> & unique_world) : _world(unique_world)
{
	setRangeOfRadius(max_radius);
	srand(time(NULL));
}

AsteroidBuilder::~AsteroidBuilder()
{
}
