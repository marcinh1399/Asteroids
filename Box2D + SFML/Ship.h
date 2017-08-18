#pragma once
#include "SFML\Graphics.hpp"
#include <array>
#include "Equipment.h"
#include "Statistics.h"
#include <string>

#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\serialization\array.hpp>


class Ship
{

private:
	friend class boost::serialization::access;

	std::array<Equipment, 6> equipment;

	Statistics basis;
	Statistics current_stats;

	sf::ConvexShape shape;

	template <typename Archive>
	void serialize(Archive &archive, const unsigned int version);

public:
	Ship(Statistics stats, sf::ConvexShape convex_shape);

	size_t levelOf(Equipment::Type type);

	void upgradeEq(Equipment::Type type);

	const sf::ConvexShape & getShape();

	const std::array<Equipment, 6> & getEquipment();

	const Statistics & getBasicsStats();

	const Statistics & getCurrentStats();

	~Ship();
};
