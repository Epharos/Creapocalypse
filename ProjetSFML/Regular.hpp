#ifndef REGULAR_HPP
#define REGULAR_HPP

#include "Enemy.hpp"

class Regular : public Enemy
{
protected:

public:
	Regular(sf::Vector2f _pos, std::string _texturePath);
	~Regular();

	void AcquireTarget(World& _world) override;
	void Attack() override;
	bool IsTargetValid(Entity*& _target) override;
};

#endif