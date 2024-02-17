#include "Hangar.hpp"
#include "GameManager.hpp"

Hangar::Hangar() : Building("grass", sf::FloatRect(0, 0, 112, 112)), m_secondHitbox(sf::FloatRect(0, 0, 48, 129))
{
	m_maxHealth = 2000;
	m_health = m_maxHealth;
	m_animation = Animation("hangar", sf::Vector2i(162, 129), 1, std::numeric_limits<float>::max());
	m_yaw = 3.15f;
}

void Hangar::Update(float _dt)
{
	LivingEntity::Update(_dt);
}

void Hangar::Draw(sf::RenderWindow& _window, Camera _camera)
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

		rect.setSize(sf::Vector2f(m_secondHitbox.width, m_secondHitbox.height));
		rect.setPosition(_camera.WorldToScreen(m_secondHitbox.getPosition()));
		_window.draw(rect);
	}

	m_animation.Draw(_window, _camera.WorldToScreen(m_position), m_yaw);
}

void Hangar::SetPosition(sf::Vector2f& _pos)
{
	m_position = _pos;
	m_hitbox.left = m_position.x - m_animation.GetFrameSize().x / TILE_SCALE / 2.0f;
	m_hitbox.top = m_position.y - m_animation.GetFrameSize().y / TILE_SCALE;
	m_secondHitbox.left = m_position.x + 1.f;
	m_secondHitbox.top = m_hitbox.top;
}

bool Hangar::IsColliding(Entity* _other)
{
	sf::FloatRect tmp = GetHitbox();
	tmp.width /= TILE_SCALE;
	tmp.height /= TILE_SCALE;

	sf::FloatRect tmp2 = m_secondHitbox;
	tmp2.width /= TILE_SCALE;
	tmp2.height /= TILE_SCALE;

	sf::FloatRect otherTmp = _other->GetHitbox();
	otherTmp.width /= TILE_SCALE;
	otherTmp.height /= TILE_SCALE;

	return tmp.intersects(otherTmp) || tmp2.intersects(otherTmp);
}