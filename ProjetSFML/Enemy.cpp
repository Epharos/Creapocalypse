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
}

Enemy::~Enemy()
{
}

void Enemy::Update(float _dt)
{
	LivingEntity::Update(_dt);

	if (m_target != nullptr)
	{
		if (m_target->IsDead())
		{
			m_target = nullptr;
		}
	}

	if (m_target == nullptr)
	{
		AcquireTarget(GameManager::GetInstance()->GetWorld());
	}

	if (m_target != nullptr)
	{
		m_targetPos = m_target->GetPosition();

		sf::Vector2f newPos = GetPosition() + Normalize(m_targetPos - GetPosition()) * m_speed * _dt;
		SetPosition(newPos);

		if (DistanceSquared(GetPosition(), m_targetPos) < m_range * m_range)
		{
			Attack();
		}
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