#include "Enemy.hpp"

#include "World.hpp"
#include "GameManager.hpp"
#include "MathUtil.hpp"

Enemy::Enemy(sf::Vector2f _pos, std::string _texturePath)
	: LivingEntity(_texturePath, sf::FloatRect(0, 0, 32, 64))
{
	SetPosition(_pos);
	m_speed = 1.f;
	m_target = nullptr;
	m_targetPos = sf::Vector2f(MAP_SIZE / 2, MAP_SIZE / 2);
	m_state = EnemyState::EnemyIdle;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float _dt)
{
	LivingEntity::Update(_dt);

	if (m_state == EnemyState::EnemyDying)
	{
		return;
	}

	if (m_target != nullptr)
	{
		if (m_target->IsDead())
		{
			m_state = EnemyState::EnemyIdle;
			m_target = nullptr;
		}
	}

	if (m_target == nullptr)
	{
		m_state = EnemyState::EnemyIdle;
		AcquireTarget(GameManager::GetInstance()->GetWorld());
	}

	if (m_target != nullptr)
	{
		if (m_state != EnemyState::EnemyAttacking)
		{
			m_targetPos = m_target->GetPosition();

			sf::Vector2f newPos = GetPosition() + Normalize(m_targetPos - GetPosition()) * m_speed * _dt;
			SetPosition(newPos);
			m_state = EnemyState::EnemyMoving;
		}

		if (IsColliding(m_target))
		{
			m_state = EnemyState::EnemyAttacking;

			if (m_attackCooldown <= 0)
			{
				Attack();
				m_attackCooldown = m_attackSpeed;
			}
		}
	}

	m_attackCooldown -= _dt;

	if (m_health <= 0)
	{
		m_state = EnemyState::EnemyDying;
	}
}

bool Enemy::IsColliding(Entity* _other)
{
	return Entity::IsColliding(_other) && CanCollideWith(_other);
}

bool Enemy::CanCollideWith(Entity*& _other)
{
	return !IsEnemy(_other);
}

void Enemy::OnCollide(Entity*& _other)
{
	
}