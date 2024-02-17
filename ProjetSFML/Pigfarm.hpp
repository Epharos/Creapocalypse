#ifndef PIGFARM_HPP
#define PIGFARM_HPP

#include "Building.hpp"

class Pigfarm : public Building
{
public:
	Pigfarm();

	virtual void Update(float _dt) override;
	virtual void Draw(sf::RenderWindow& _window, Camera _camera) override;
};

#endif