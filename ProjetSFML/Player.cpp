#include "Player.hpp"
#include "GameManager.hpp"
#include "MathUtil.hpp"

Player::Player(std::string _texturePath, sf::FloatRect _hitbox) : 
	LivingEntity(_texturePath, _hitbox), m_state(PlayerState::Idle), m_walkingAnimation("assets/player/moving.png", sf::Vector2i(32, 64), 10, 0.1f)
{
	m_animation = Animation(_texturePath, sf::Vector2i(32, 64), 4, 0.1f);
	m_speed = 5.f;
	m_position = sf::Vector2f(125, 125);
	m_money = 100.f;
}

void Player::Update(float _dt)
{
	LivingEntity::Update(_dt);

	m_walkingAnimation.Update(_dt);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_state != Crafting)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(GameManager::GetInstance()->GetWindow());
			m_targetPosition = sf::Vector2f(GameManager::GetInstance()->GetCamera().ScreenToWorld(sf::Vector2f(mousePos)));
		}
	}

	if (DistanceSquared(m_position, m_targetPosition) > .01f)
	{
		m_state = Moving;
		sf::Vector2f dir = m_targetPosition - m_position;
		dir = Normalize(dir) * m_speed;
		sf::Vector2f newPos = m_position + dir * _dt;
		SetPosition(newPos);
		m_yaw = atan2(dir.y, dir.x) + 3.1415;
	}
	else
	{
		m_state = Idle;
	}
}

void Player::Draw(sf::RenderWindow& _window, Camera _camera)
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