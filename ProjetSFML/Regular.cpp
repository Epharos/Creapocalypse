#include "Regular.hpp"

#include <ranges>
#include "World.hpp"
#include "MathUtil.hpp"

Regular::Regular(sf::Vector2f _pos, std::string _texturePath)
	: Enemy(_pos, _texturePath)
{
	m_damage = 10.f;
	m_attackSpeed = 1.f;
	m_range = 1.f;

	m_speed = .5f;
	m_animation = Animation(_texturePath, sf::Vector2i(32, 64), 4, 0.1f);
}

Regular::~Regular()
{
}

void Regular::AcquireTarget(World& _world)
{
	auto entities = _world.GetEntities() |
		std::views::filter([this](Entity* _entity) { return IsTargetValid(_entity); });

	std::list<Entity*> targets;
	targets.insert(targets.begin(), entities.begin(), entities.end());

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