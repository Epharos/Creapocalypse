#include "BaseTurret.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "GameManager.hpp"

BaseTurret::BaseTurret(sf::Vector2f _pos, float _rotation, float _range, float _fireRate, float _spread)
	: LivingEntity("lmg", sf::FloatRect(0, 0, 36, 44))
{
	m_range = _range;
	m_fireRate = _fireRate;
	m_spread = _spread;
	SetPosition(_pos);
	m_speed = .0f;
	m_target = nullptr;
	m_yaw = _rotation;
	m_cost = 10.f;
	m_fireTimer = 0.f;
	m_state = TurretState::Spawning;
}

bool BaseTurret::IsPlaceable(Player*& _player, World& _world)
{
	return _player->GetMoney() >= m_cost;
	//TODO : Check if the turret is not colliding with anything
	//TODO : Check if the turret is not too far away from the player
}

void BaseTurret::SetTarget(Entity* _target)
{
	m_target = _target;
}

void BaseTurret::Update(float _dt)
{
	Entity::Update(_dt);

	m_fireTimer += _dt;
	if (m_state != TurretState::Spawning && m_state != TurretState::Dying)
	{
		if (m_target != nullptr)
		{
			sf::Vector2f dir = m_target->GetPosition() - m_position;
			m_yaw = atan2(dir.y, dir.x);

			m_state = TurretState::Shooting;

			if (m_fireTimer >= 1.f / m_fireRate)
			{
				Shoot();
				m_fireTimer = 0.f;
			}
		}
		else
		{
			m_state = TurretState::Searching;
			AcquireTarget(GameManager::GetInstance()->GetWorld());
		}
	}
}