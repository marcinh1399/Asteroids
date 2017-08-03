#pragma once
class Equipment
{

private:
	unsigned int current_level;

	float multiplier_per_level = 1.3;

	const int max_level = 10;

public:
 // remember to initilize



	struct Stats
	{
		unsigned int hp{ 0 };
		unsigned int speed{ 0 };
		unsigned int radians_per_second{ 0 };
		unsigned int armor{ 0 };
		unsigned int damage_of_bullets{ 0 };
		unsigned int bullet_cooldown{ 0 };
	};

	Stats stats;

	
	void makeHP(const unsigned int & level);


	void makeEngine(const unsigned int & level);


	void makeAgility(const unsigned int & level);

	
	void makeArmor(const unsigned int & level);
	

	void makeBullet(const unsigned int & level);


	void makeGun(const unsigned int & level);

	

	Equipment();
	~Equipment();
};

