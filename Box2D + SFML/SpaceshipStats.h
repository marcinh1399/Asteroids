#pragma once
class SpaceshipStats
{

private:
	unsigned int hp;
	unsigned int speed;
	unsigned int radians_per_second;
	unsigned int basic_armor;
	unsigned int basic_damage_of_bullets;
	unsigned int basic_bullet_cooldown;

	SpaceshipStats * _type1;
	SpaceshipStats * _type2;
	///...

	void initType1();

	void initType2();

	///...
	

public:
	SpaceshipStats();

	SpaceshipStats * getType1();

	SpaceshipStats * getType2();

	///...
	
	~SpaceshipStats();
};

