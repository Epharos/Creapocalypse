#include "BaseTurret.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "GameManager.hpp"

BaseTurret::BaseTurret(sf::Vector2f _pos, float _rotation, float _range, float _fireRate, float _spread)
	: LivingEntity("assets/turrets/lmg.png", sf::FloatRect(0, 0, 36, 44)), m_range(m_range), m_fireRate(m_fireRate), m_spread(m_spread)
{
	SetPosition(_pos);
	m_speed = .0f;
	m_target = nullptr;
	m_yaw = _rotation;
	m_cost = 10.f;
}

bool BaseTurret::IsPlaceable(Player*& _player, World& _world)
{
	return _player->GetMoney() >= m_cost;
	//TODO : Check if the turret is not colliding with anything
	//TODO : Check if the turret is not too far away from the player
}

void BaseTurret::SetTarget(Entity*& _target)
{
	m_target = _target;
}

void BaseTurret::Update(float _dt)
{
	if (m_target != nullptr)
	{
		if (IsTargetValid(m_target))
		{
			Shoot();
		}
		else
		{
			m_target = nullptr;
		}
	}
	else
	{
		AcquireTarget(GameManager::GetInstance()->GetWorld());
	}
}

void BaseTurret::Draw(sf::RenderWindow* _window)
{
	//TODO : Draw the turret
}