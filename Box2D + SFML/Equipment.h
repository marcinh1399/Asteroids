#pragma once
class Equipment
{

private:

	enum class Type
	{
		hp,
		engine,
		agility,
		armor,
		bullet,
		gun
	};

	Type type;

	const int max_level{ 10 };
	unsigned int current_level{ 0 };

	const float multiplier_per_level{ 1.2f };
	const float multiplier_cooldown{ 0.9f };

public:

	struct Stats
	{
		float hp{ 1.f };
		float speed{ 1.f };
		float radians_per_second{ 1.f };
		float armor{ 1.f };
		float damage_of_bullets{ 1.f };
		float bullet_cooldown{ 1.f };
	};

	Stats stats;

	
	void makeHP();

	void makeEngine();

	void makeAgility();
	
	void makeArmor();

	void makeBullet();

	void makeGun();

	
	bool nextLevel();

	
};

