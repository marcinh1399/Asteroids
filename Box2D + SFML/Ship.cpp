#include "stdafx.h"
#include "Ship.h"



Ship::Ship(Statistics stats, sf::ConvexShape convex_shape)
	: basis(stats),
	current_stats(stats),
	shape(convex_shape)
{
	for (int i = 0; i < 6; ++i)
	{
		equipment[i].init(static_cast<Equipment::Type>(i));
	}
}

size_t Ship::levelOf(Equipment::Type type)
{
	return equipment[static_cast<int>(type)].getLevel();
}

void Ship::upgradeEq(Equipment::Type type)
{
	equipment[static_cast<int>(type)].nextLevel();
	

	current_stats = basis;
	for (int i = 0; i < 6; ++i)
	{
		current_stats += equipment[i].stats;
	}
}

const sf::ConvexShape & Ship::getShape()
{
	return shape;
}

const std::array<Equipment, 6>& Ship::getEquipment()
{
	return equipment;
}

const Statistics & Ship::getBasicsStats()
{
	return basis;
}

const Statistics & Ship::getCurrentStats()
{
	current_stats = basis;
	for (int i = 0; i < 6; ++i)
	{
		current_stats += equipment[i].stats;
	}

	return current_stats;
}


Ship::~Ship()
{

}



template<typename Archive>
inline void Ship::serialize(Archive & archive, const unsigned int version)
{
	archive & equipment;
}