#include "LMGTurret.hpp"

#include <ranges>

#include "MathUtil.hpp"

#include "World.hpp"
#include "Bullet.hpp"
#include "GameManager.hpp"

LightMachineGunTurret::LightMachineGunTurret(sf::Vector2f _pos, float _rotation) :
	BaseTurret(_pos, _rotation, 12.f, 3.f, 0.1f),
	m_spawingAnimation("lmg_spawning", sf::Vector2i(72, 72), 5, 0.08f),
	m_shootingAnimation("lmg_firing", sf::Vector2i(102, 72), 8, 0.1f)
{
	SetPosition(_pos);
	m_maxHealth = 100.f;
	m_health = m_maxHealth;
	m_animation = Animation("lmg", sf::Vector2i(102, 72), 4, 0.6f);
	m_spawingAnimation.Once();
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

	GameManager::GetInstance()->GetWorld().SpawnEntity(new Bullet(bulletPos, angle, 12.f, 10.f, 24.f, "bullet"));
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

void LightMachineGunTurret::Update(float _dt)
{
	BaseTurret::Update(_dt);

	if (!m_target || !IsTargetValid(m_target))
	{
		m_target = nullptr;
	}

	if (m_state == TurretState::Spawning)
	{
		m_spawingAnimation.Update(_dt);

		if (m_spawingAnimation.IsDone())
		{
			m_state = TurretState::Searching;
		}
	}
	else if (m_state == TurretState::Shooting)
	{
		m_shootingAnimation.Update(_dt);
	}
}

void LightMachineGunTurret::Draw(sf::RenderWindow& _window, Camera _camera)
{
	if (!ShouldBeRendered(_camera, _window))
	{
		return;
	}

	if (GameManager::GetInstance()->GetDebugMode())
	{
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(m_hitbox.width, m_hitbox.height));
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Red);
		rect.setOutlineThickness(1);
		rect.setPosition(_camera.WorldToScreen(m_hitbox.getPosition()));
		_window.draw(rect);
	}

	switch (m_state)
	{
		case TurretState::Spawning:
			m_spawingAnimation.Draw(_window, _camera.WorldToScreen(m_position), m_yaw + 3.1415);
			break;
		case TurretState::Searching:
			m_animation.Draw(_window, _camera.WorldToScreen(m_position), m_yaw + 3.1415);
			break;
		case TurretState::Shooting:
			m_shootingAnimation.Draw(_window, _camera.WorldToScreen(m_position), m_yaw + 3.1415);
			break;
		case TurretState::Dying:
			break;
		default:
			m_animation.Draw(_window, _camera.WorldToScreen(m_position), m_yaw + 3.1415);
			break;
	}
}

void LightMachineGunTurret::SetPosition(sf::Vector2f& _pos)
{
	BaseTurret::SetPosition(_pos);
	m_hitbox.top = m_position.y - 44.f / TILE_SCALE;
}