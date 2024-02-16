#ifndef HANGAR_HPP
#define HANGAR_HPP

#include "Building.hpp"

class Hangar : public Building
{
private:
	sf::FloatRect m_secondHitbox;

public:
	Hangar();
	~Hangar() {};

	void Update(float _dt);
	void Draw(sf::RenderWindow& _window, Camera _camera);
	bool IsDead();
	void Kill();
	bool IsColliding(Entity* _other);

	void SetPosition(sf::Vector2f& _pos);

	sf::FloatRect GetSecondHitbox() const { return m_secondHitbox; }
};

#endif