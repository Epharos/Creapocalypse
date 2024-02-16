#ifndef BARN_HPP
#define BARN_HPP

#include "LivingEntity.hpp"

class Barn : public LivingEntity
{
public:
	Barn();

	virtual void Update(float _dt) override;
	virtual void Draw(sf::RenderWindow& _window, Camera _camera) override;
	virtual bool IsDead() override;
	virtual void Kill() override;
};

#endif