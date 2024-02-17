#ifndef BARN_HPP
#define BARN_HPP

#include "Building.hpp"

class Barn : public Building
{
public:
	Barn();

	virtual void Update(float _dt) override;
	virtual void Draw(sf::RenderWindow& _window, Camera _camera) override;
};

#endif