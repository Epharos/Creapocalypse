#ifndef BASETURRET_HPP
#define BASETURRET_HPP

#include "LivingEntity.hpp"

class Player;
class World;

enum TurretState
{
	Spawning,
	Searching,
	Shooting,
	Dying,
	Placeholder
};

class BaseTurret : public LivingEntity
{
protected:
	float m_range; 
	float m_fireRate; //bullets per second
	float m_spread; //accuracy as radians
	float m_cost;

	float m_bulletDamage;
	float m_bulletSpeed;
	float m_bulletRange;
	float m_fireTimer;

	std::string m_turretName;
	std::string m_turretDescription;

	Entity* m_target;

	TurretState m_state;

public:
	BaseTurret(sf::Vector2f _pos, float _rotation, float _range, float _fireRate, float _spread);

	bool IsPlaceable(Player*& _player, World& _world);
	void SetTarget(Entity* _target);

	virtual void Update(float _dt);

	virtual void Shoot() = 0;
	virtual bool IsTargetValid(Entity*& _target) = 0;
	virtual void AcquireTarget(World& _world) = 0;

	float GetCost() { return m_cost; }
	float GetRange() { return m_range; }
	float GetFireRate() { return m_fireRate; }
	float GetSpread() { return m_spread; }
	std::string GetName() { return m_turretName; }
	std::string GetDescription() { return m_turretDescription; }

	float GetBulletDamage() { return m_bulletDamage; }
	float GetBulletSpeed() { return m_bulletSpeed; }
	float GetBulletRange() { return m_bulletRange; }

	Entity* GetTarget() { return m_target; }

	TurretState GetState() { return m_state; }
	void SetState(TurretState _state) { m_state = _state; }

	virtual BaseTurret* Clone() = 0;
};

#endif