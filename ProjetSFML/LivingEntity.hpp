#ifndef LIVINGENTITY__HPP
#define LIVINGENTITY__HPP

#include "Entity.hpp"

class LivingEntity : public Entity
{
protected:
	unsigned int m_health;
	unsigned int m_maxHealth;

public:
	LivingEntity(std::string _texturePath, sf::FloatRect _hitbox) : Entity(_texturePath, _hitbox), m_health(100), m_maxHealth(100) {}

	/// <summary>
	/// Hurts the entity by a certain amount
	/// </summary>
	/// <param name="_damage">Damages delt to the Living entity</param>
	void Hurt(unsigned int _damage);

	/// <summary>
	/// Heals the entity by a certain amount
	/// </summary>
	/// <param name="_heal">HP given to the Living entity</param>
	void Heal(unsigned int _heal);

	unsigned int GetHealth() const { return m_health; }
	unsigned int GetMaxHealth() const { return m_maxHealth; }

	virtual bool IsDead() override;
	virtual void Kill() override;
};

#endif