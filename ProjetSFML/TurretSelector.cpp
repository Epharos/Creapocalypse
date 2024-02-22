#include "TurretSelector.hpp"

TurretSelector::TurretSelector(sf::Vector2f _position, TurretSelection* _parent) : Widget(_position, sf::Vector2f(132, 174), "turretSelector"), m_parent(_parent)
{
	
}

TurretSelector::~TurretSelector()
{
	delete m_turret;
}

void TurretSelector::SetTurretSprite(std::string _texture)
{
	m_turretSprite.setTexture(*TextureManager::GetTexture(_texture));
	m_turretSprite.setTextureRect(sf::IntRect(29, 26, 40, 46));
	m_turretSprite.setScale(3, 3);
}

void TurretSelector::Update(float _dt)
{
	Widget::Update(_dt);
}

void TurretSelector::Draw(sf::RenderWindow& _window)
{
	if (m_active)
	{
		m_background.setTextureRect(sf::IntRect(132, 0, 132, 174));
	}
	else
	{
		m_background.setTextureRect(sf::IntRect(0, 0, 132, 174));
	}

	Widget::Draw(_window);

	m_turretSprite.setPosition(m_position.x + 4, m_position.y + 4 + (m_active ? 12 : 0));
	_window.draw(m_turretSprite);
}

void TurretSelector::OnClick(sf::Vector2i _mousePos)
{
	for (Widget* widget : m_parent->GetWidgets())
	{
		TurretSelector* selector = dynamic_cast<TurretSelector*>(widget);
		if (selector != nullptr)
		{
			selector->m_active = false;
		}
	}

	m_active = true;
	m_parent->m_selectedTurret = this;
}