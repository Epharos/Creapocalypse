#ifndef GARAGE__HPP
#define GARAGE__HPP

#include "Building.hpp"

class Garage : public Building
{
private:
	sf::FloatRect m_secondHitbox;

public:
	Garage();
	~Garage() {};

	void Update(float _dt);
	void Draw(sf::RenderWindow& _window, Camera _camera);
	bool IsColliding(Entity* _other);

	void SetPosition(sf::Vector2f& _pos);

	sf::FloatRect GetSecondHitbox() const { return m_secondHitbox; }
};

#endif