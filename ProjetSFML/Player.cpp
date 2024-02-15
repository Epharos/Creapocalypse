#include "Player.hpp"

Player::Player(std::string _texturePath, sf::FloatRect _hitbox) : 
	LivingEntity(_texturePath, _hitbox), m_state(PlayerState::Idle), m_walkingAnimation("assets/player/moving.png", sf::Vector2i(32, 64), 4, 0.1f)
{
	m_animation = Animation(_texturePath, sf::Vector2i(32, 64), 4, 0.1f);
}

void Player::Update(float _dt)
{
	LivingEntity::Update(_dt);

	m_walkingAnimation.Update(_dt);
}

void Player::Draw(sf::RenderWindow& _window, Camera _camera)
{
	if (!ShouldBeRendered(_camera, _window))
	{
		return;
	}

	switch (m_state)
	{
	case Idle:
		m_animation.Draw(_window, _camera.WorldToScreen(m_position), m_yaw);
		break;
	case Moving:
		m_walkingAnimation.Draw(_window, _camera.WorldToScreen(m_position), m_yaw);
		break;
	case Crafting:
		m_animation.Draw(_window, _camera.WorldToScreen(m_position), m_yaw);
		break;
	default:
		m_animation.Draw(_window, _camera.WorldToScreen(m_position), m_yaw);
		break;
	}
}

bool Player::IsDead()
{
	return m_health <= 0;
}

void Player::Kill()
{
	m_health = 0;
}