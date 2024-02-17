#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "LivingEntity.hpp"

class Building : public LivingEntity
{
public:
	Building(std::string _texturePath, sf::FloatRect _hitbox) : LivingEntity(_texturePath, _hitbox) {}
};

#endif