#ifndef PIGFARM_HPP
#define PIGFARM_HPP

#include "LivingEntity.hpp"

class Pigfarm : public LivingEntity
{
public:
	Pigfarm();

	virtual void Update(float _dt) override;
	virtual void Draw(sf::RenderWindow& _window, Camera _camera) override;
	virtual bool IsDead() override;
	virtual void Kill() override;
};

#endif