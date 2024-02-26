#include "Regular.hpp"

#include <ranges>
#include "World.hpp"
#include "MathUtil.hpp"

Regular::Regular(sf::Vector2f _pos)
	: Enemy(_pos, "regularIdle"), m_movingAnimation("regularMoving", sf::Vector2i(72, 72), 10, 0.075f),
	m_attackingAnimation("regularAttacking", sf::Vector2i(72, 72), 5, 0.1f), m_dyingAnimation("regularDying", sf::Vector2i(102, 72), 9, 0.07f)
{
	m_damage = 10.f;
	m_attackSpeed = 1.f;
	m_range = 1.f;

	m_speed = 3.5f;
	m_animation = Animation("regularIdle", sf::Vector2i(72, 72), 4, 0.1f);
	m_dyingAnimation.Once();
}

Regular::~Regular()
{
}

void Regular::AcquireTarget(World& _world)
{
	std::list<Entity*> targets = std::list(_world.GetEntities());
	targets.remove_if([this](Entity* _entity) { return !IsTargetValid(_entity); });

	targets.sort([this](Entity* _a, Entity* _b)
		{
			return DistanceSquared(GetPosition(), _a->GetPosition()) < DistanceSquared(GetPosition(), _b->GetPosition());
		});

	if (!targets.empty())
	{
		m_target = targets.front();
	}
}

void Regular::Attack()
{
	if (m_target != nullptr)
	{
		LivingEntity* livingTarget = dynamic_cast<LivingEntity*>(m_target);
		livingTarget->Hurt(m_damage);
	}
}

bool Regular::IsTargetValid(Entity*& _target)
{
	return !IsEnemy(_target);
}

bool Regular::IsDead()
{
	return LivingEntity::IsDead() && m_dyingAnimation.IsDone();
}

void Regular::Update(float _dt)
{
	Enemy::Update(_dt);

	m_movingAnimation.Update(_dt);

	if (m_state == EnemyAttacking)
	{
		m_attackingAnimation.Update(_dt);

		if (m_attackingAnimation.IsDone())
		{
			m_state = EnemyIdle;
			m_attackingAnimation.Reset();
		}
	}
	else if (m_state == EnemyDying)
	{
		m_dyingAnimation.Update(_dt);
	}
}

void Regular::Draw(sf::RenderWindow& _window, Camera _camera)
{
	if (!ShouldBeRendered(_camera, _window))
	{
		return;
	}

	switch (m_state)
	{
	case EnemyIdle:
		m_animation.Draw(_window, _camera.WorldToScreen(GetPosition()), m_yaw);
		break;
	case EnemyMoving:
		m_movingAnimation.Draw(_window, _camera.WorldToScreen(GetPosition()), m_yaw);
		break;
	case EnemyAttacking:
		m_attackingAnimation.Draw(_window, _camera.WorldToScreen(GetPosition()), m_yaw);
		break;
	case EnemyDying:
		m_dyingAnimation.Draw(_window, _camera.WorldToScreen(GetPosition()), m_yaw);
		break;
	}
}