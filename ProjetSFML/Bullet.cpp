#include "Bullet.hpp"

#include "World.hpp"
#include "GameManager.hpp"

Bullet::Bullet(sf::Vector2f _pos, float _rotation, float _speed, float _damage, float _range, std::string _texturePath)
	: LivingEntity(_texturePath, sf::FloatRect(0, 0, 5, 5))
{
	m_speed = _speed;
	m_damage = _damage;
	m_range = _range;
	SetPosition(_pos);
	m_yaw = _rotation;
	m_animation = Animation(_texturePath, sf::Vector2i(15, 5), 1, std::numeric_limits<float>::max());
}

Bullet::~Bullet()
{
}

void Bullet::Update(float _dt)
{
	Entity::Update(_dt);

	sf::Vector2f dir = sf::Vector2f(cos(m_yaw), sin(m_yaw));
	sf::Vector2f newPos = GetPosition() + dir * m_speed * _dt;
	SetPosition(newPos);

	m_range -= m_speed * _dt;

	for (auto& entity : GameManager::GetInstance()->GetWorld().GetEntities())
	{
		if (entity != this)
		{
			if (entity->IsColliding(this))
			{
				if (dynamic_cast<LivingEntity*>(entity) != nullptr)
				{
					LivingEntity* livingEntity = dynamic_cast<LivingEntity*>(entity);
					livingEntity->Hurt(m_damage);
				}

				Kill();
			}
		}
	}
}

bool Bullet::IsDead()
{
	return m_range <= 0;
}

void Bullet::Kill()
{
	m_range = 0;
}