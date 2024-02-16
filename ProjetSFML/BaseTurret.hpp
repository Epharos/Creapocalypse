#ifndef BASETURRET_HPP
#define BASETURRET_HPP

#include "LivingEntity.hpp"

class Player;
class World;

class BaseTurret : public LivingEntity
{
protected:
	float m_range; 
	float m_fireRate; //bullets per second
	float m_spread; //accuracy as radians

	float m_cost;

	Entity* m_target;

public:
	BaseTurret(sf::Vector2f _pos, float _rotation, float _range, float _fireRate, float _spread);

	bool IsPlaceable(Player*& _player, World& _world);
	void SetTarget(Entity*& _target);

	virtual void Update(float _dt);
	virtual void Draw(sf::RenderWindow* _window);

	virtual void Shoot() = 0;
	virtual bool IsTargetValid(Entity*& _target) = 0;
	virtual void AcquireTarget(World& _world) = 0;
};

#endif