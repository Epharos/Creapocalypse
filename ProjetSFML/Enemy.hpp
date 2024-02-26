#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "LivingEntity.hpp"

class World;

enum EnemyState
{
	EnemyIdle,
	EnemyMoving,
	EnemyAttacking,
	EnemyDying
};

class Enemy : public LivingEntity
{
protected:
	float m_damage;
	float m_range;
	float m_attackSpeed;
	float m_attackCooldown;

	Entity* m_target;
	sf::Vector2f m_targetPos;

	EnemyState m_state;

	public:
		Enemy(sf::Vector2f _pos, std::string _texturePath);
		~Enemy();

		void Update(float _dt) override;

		virtual void AcquireTarget(World& _world) = 0;
		virtual void Attack() = 0;
		virtual bool IsTargetValid(Entity*& _target) = 0;

		bool IsColliding(Entity* _other) override;
		bool CanCollideWith(Entity*& _other) override;
		void OnCollide(Entity*& _other) override;
};

#endif