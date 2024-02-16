#ifndef HOUSE__HPP
#define HOUSE__HPP

#include "Building.hpp"

class House : public Building
{
public:
	House();

	virtual void Update(float _dt) override;
	virtual void Draw(sf::RenderWindow& _window, Camera _camera) override;
	virtual bool IsDead() override;
	virtual void Kill() override;
};

#endif