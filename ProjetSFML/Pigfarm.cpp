#include "Pigfarm.hpp"

Pigfarm::Pigfarm() : Building("assets/buildings/pigfarm.png", sf::FloatRect(0, 0, 336, 160))
{
	m_maxHealth = 3000;
	m_health = m_maxHealth;
	m_animation = Animation("assets/buildings/pigfarm.png", sf::Vector2i(336, 160), 1, std::numeric_limits<float>::max());
	m_yaw = 3.15f;
}

void Pigfarm::Update(float _dt)
{
	LivingEntity::Update(_dt);
}

void Pigfarm::Draw(sf::RenderWindow& _window, Camera _camera)
{
	LivingEntity::Draw(_window, _camera);
}