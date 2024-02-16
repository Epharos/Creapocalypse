#include "House.hpp"
#include "GameManager.hpp"

House::House() : LivingEntity("assets/buildings/house.png", sf::FloatRect(0, 0, 138, 185))
{
	m_maxHealth = 1000;
	m_health = m_maxHealth;
	m_animation = Animation("assets/buildings/house.png", sf::Vector2i(140, 185), 1, std::numeric_limits<float>::max());
	m_yaw = 3.15f;
}

void House::Update(float _dt)
{
	Entity::Update(_dt);
}

void House::Draw(sf::RenderWindow& _window, Camera _camera)
{
	Entity::Draw(_window, _camera);
}

bool House::IsDead()
{
	return m_health <= 0;
}

void House::Kill()
{
	m_health = 0;
}