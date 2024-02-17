#include "Barn.hpp"

Barn::Barn() : Building("grass", sf::FloatRect(0, 0, 112, 104))
{
	m_maxHealth = 3000;
	m_health = m_maxHealth;
	m_animation = Animation("barn", sf::Vector2i(112, 104), 1, std::numeric_limits<float>::max());
	m_yaw = 3.15f;
}

void Barn::Update(float _dt)
{
	Entity::Update(_dt);
}

void Barn::Draw(sf::RenderWindow& _window, Camera _camera)
{
	Entity::Draw(_window, _camera);
}