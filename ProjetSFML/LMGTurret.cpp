#include "LMGTurret.hpp"

#include <ranges>

#include "MathUtil.hpp"

#include "World.hpp"
#include "Bullet.hpp"
#include "GameManager.hpp"

LightMachineGunTurret::LightMachineGunTurret(sf::Vector2f _pos, float _rotation) :
	BaseTurret(_pos, _rotation, 12.f, 3.f, 0.1f)
{
	m_maxHealth = 100.f;
	m_health = m_maxHealth;
}

void LightMachineGunTurret::Shoot()
{
	if (m_target == nullptr)
	{
		return;
	}

	sf::Vector2f dir = m_target->GetPosition() - m_position;
	float angle = atan2(dir.y, dir.x);
	float spread = (rand() / (float)RAND_MAX - 0.5f) * m_spread;
	angle += spread;

	sf::Vector2f bulletPos = m_position + sf::Vector2f(cos(angle), sin(angle));

	GameManager::GetInstance()->GetWorld().SpawnEntity(new Bullet(bulletPos, angle, 1.f, 10.f, 24.f, "assets/turrets/bullet.png"));
}

bool LightMachineGunTurret::IsTargetValid(Entity*& _target)
{
	return IsPlayer(_target) && DistanceSquared(GetPosition(), _target->GetPosition()) < (m_range * m_range);
}

void LightMachineGunTurret::AcquireTarget(World& _world)
{
	auto entities = _world.GetEntities() |
		std::views::filter([this](Entity* _entity) { return IsTargetValid(_entity); });

	std::list<Entity*> targets;
	targets.resize(std::distance(entities.begin(), entities.end()));
	std::copy(entities.begin(), entities.end(), targets.begin());

	targets.sort([this](Entity* _a, Entity* _b)
		{
			return DistanceSquared(GetPosition(), _a->GetPosition()) < DistanceSquared(GetPosition(), _b->GetPosition());
		});

	if (!targets.empty())
	{
		m_target = targets.front();
	}
}