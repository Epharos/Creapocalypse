#include "LivingEntity.hpp"

void LivingEntity::Hurt(unsigned int _damage)
{
	if (_damage > m_health)
	{
		_damage = m_health;
	}

	m_health -= _damage;
}

void LivingEntity::Heal(unsigned int _heal)
{
	m_health += _heal;

	if (m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
}