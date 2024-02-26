#include "ShotgunTurret.hpp"

#include "MathUtil.hpp"

#include "World.hpp"
#include "Bullet.hpp"
#include "GameManager.hpp"

ShotgunTurret::ShotgunTurret(sf::Vector2f _pos, float _rotation) :
	BaseTurret(_pos, _rotation, 5.f, 1.f, 0.14f),
	m_spawingAnimation("shotgun_spawning", sf::Vector2i(72, 72), 5, 0.08f),
	m_shootingAnimation("shotgun_firing", sf::Vector2i(102, 72), 3, 0.1f)
{
	SetPosition(_pos);
	m_maxHealth = 100.f;
	m_health = m_maxHealth;
	m_animation = Animation("shotgun", sf::Vector2i(102, 72), 4, 0.6f);
	m_spawingAnimation.Once();

	m_turretName = "Shotgun Turret";
	m_turretDescription = "3 bullets at once to make sure this fucker is *dead* dead";

	m_bulletDamage = 15.f;
	m_bulletSpeed = 4.f;
	m_bulletRange = 10.f;

	m_cost = 5.5f;
}

void ShotgunTurret::Shoot()
{
	if (m_target == nullptr)
	{
		return;
	}

	sf::Vector2f dir = m_target->GetPosition() - m_position;
	float angle = atan2(dir.y, dir.x);
	float spread = (rand() / (float)RAND_MAX - 0.5f) * m_spread;
	angle += spread;

	sf::Vector2f bulletPos = m_position - sf::Vector2f(0, 22.f / TILE_SCALE) + sf::Vector2f(cos(angle), sin(angle));

	GameManager::GetInstance()->GetWorld().SpawnEntity(new Bullet(bulletPos, angle, m_bulletSpeed, m_bulletDamage, m_bulletRange, "bullet"));
	GameManager::GetInstance()->GetWorld().SpawnEntity(new Bullet(bulletPos, angle + 0.2, m_bulletSpeed, m_bulletDamage, m_bulletRange, "bullet"));
	GameManager::GetInstance()->GetWorld().SpawnEntity(new Bullet(bulletPos, angle - 0.2, m_bulletSpeed, m_bulletDamage, m_bulletRange, "bullet"));
}

bool ShotgunTurret::IsTargetValid(Entity*& _target)
{
	return IsEnemy(_target) && DistanceSquared(GetPosition(), _target->GetPosition()) < (m_range * m_range);
}

void ShotgunTurret::AcquireTarget(World& _world)
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

void ShotgunTurret::Update(float _dt)
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

void ShotgunTurret::Draw(sf::RenderWindow& _window, Camera _camera)
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
	case TurretState::Placeholder:
		m_animation.GetSprite().setColor(!IsPlaceable(GameManager::GetInstance()->GetPlayer(), GameManager::GetInstance()->GetWorld()) ? sf::Color::Red : sf::Color::Blue);
		m_animation.Draw(_window, _camera.WorldToScreen(m_position), m_yaw + 3.1415);
		break;
	default:
		m_animation.Draw(_window, _camera.WorldToScreen(m_position), m_yaw + 3.1415);
		break;
	}
}

void ShotgunTurret::SetPosition(sf::Vector2f& _pos)
{
	BaseTurret::SetPosition(_pos);
	m_hitbox.top = m_position.y - 44.f / TILE_SCALE;
}

BaseTurret* ShotgunTurret::Clone()
{
	return new ShotgunTurret(m_position, m_yaw);
}