#include "Player.hpp"
#include "GameManager.hpp"
#include "MathUtil.hpp"

#include "TurretSelection.hpp"

#include "BaseTurret.hpp"

Player::Player(std::string _texturePath, sf::FloatRect _hitbox) : 
	LivingEntity(_texturePath, _hitbox), m_state(PlayerState::Idle), m_walkingAnimation("player_walk", sf::Vector2i(32, 64), 10, 0.1f)
{
	m_animation = Animation(_texturePath, sf::Vector2i(32, 64), 4, 0.1f);
	m_speed = 5.f;
	sf::Vector2f pos = sf::Vector2f(20, 20);
	SetPosition(pos);
	m_targetPosition = m_position;
	m_money = 25.f;
	m_maxHealth = 100.f;
	m_health = m_maxHealth;
}

void Player::Update(float _dt)
{
	LivingEntity::Update(_dt);

	m_walkingAnimation.Update(_dt);

	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_state != Crafting)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(GameManager::GetInstance()->GetWindow());
			m_targetPosition = sf::Vector2f(GameManager::GetInstance()->GetCamera().ScreenToWorld(sf::Vector2f(mousePos)));
		}
	}*/

	if(m_state == Placing && m_placingTurret == nullptr)
	{
		SetState(Idle);
	}

	if (m_state != Crafting && m_state != Placing)
	{
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
	else
	{
		m_targetPosition = m_position;
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

	sf::Vector2f turretWorldPos = _camera.ScreenToWorld(sf::Vector2f(sf::Mouse::getPosition(GameManager::GetInstance()->GetWindow())));

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
	case Placing:
		m_animation.Draw(_window, _camera.WorldToScreen(m_position), m_yaw);
		m_placingTurret->SetPosition(turretWorldPos);
		m_placingTurret->Draw(_window, _camera);
		break;
	default:
		m_animation.Draw(_window, _camera.WorldToScreen(m_position), m_yaw);
		break;
	}
}

void Player::RealTimeKeyboardInput()
{
	
}

void Player::RealTimeMouseInput(sf::Vector2i _mousePos)
{
	
}

void Player::EventKeyboardInput(sf::Keyboard::Key _key, sf::Event::KeyEvent _event)
{
	if (_key == sf::Keyboard::C)
	{
		if (m_state == Crafting)
		{
			GameManager::GetInstance()->CloseUI();
			m_state = Idle;
		}
		else
		{
			m_state = Crafting;
			GameManager::GetInstance()->OpenUI(new TurretSelection());
		}
	}
}

void Player::EventMouseInput(sf::Mouse::Button _button, sf::Vector2i _mousePos)
{
	if (_button == sf::Mouse::Left)
	{
		if (m_state != Crafting && m_state != Placing)
		{
			m_targetPosition = sf::Vector2f(GameManager::GetInstance()->GetCamera().ScreenToWorld(sf::Vector2f(_mousePos)));
		}

		if(m_state == Placing)
		{
			if(m_placingTurret != nullptr)
			{
				if (m_placingTurret->IsPlaceable(GameManager::GetInstance()->GetPlayer(), GameManager::GetInstance()->GetWorld()))
				{
					m_money -= m_placingTurret->GetCost();
					GameManager::GetInstance()->GetWorld().SpawnEntity(m_placingTurret->Clone());
				}
			}
		}
	}

if (_button == sf::Mouse::Right)
	{
		if (m_state == Placing)
		{
			SetState(Idle);
			delete m_placingTurret;
			m_placingTurret = nullptr;
		}
	}
}