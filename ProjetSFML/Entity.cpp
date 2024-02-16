#include "Entity.hpp"
#include "GameManager.hpp"

Entity::Entity(std::string _texturePath, sf::FloatRect _hitbox) :
	m_position(0, 0), m_hitbox(_hitbox), m_yaw(0.f), m_animation(_texturePath, sf::Vector2i(32, 64), 1, std::numeric_limits<float>::max()), m_speed(0.0f)
{
	
}

void Entity::Update(float _dt)
{
	m_animation.Update(_dt);
}

void Entity::Draw(sf::RenderWindow& _window, Camera _camera)
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

	m_animation.Draw(_window, _camera.WorldToScreen(m_position), m_yaw);
}

bool Entity::ShouldBeRendered(Camera _camera, sf::RenderWindow& _window)
{
	sf::Vector2f screenPos = _camera.WorldToScreen(m_position);
	sf::Vector2i size = m_animation.GetFrameSize();

	return screenPos.x + size.x / 2 > 0 && screenPos.x - size.x / 2 < _window.getSize().x && screenPos.y + size.y > 0 && screenPos.y < _window.getSize().y + size.y;
}

void Entity::SetPosition(sf::Vector2f& _pos)
{
	m_position = _pos;
	m_hitbox.left = m_position.x - m_animation.GetFrameSize().x / TILE_SCALE / 2.0f;
	m_hitbox.top = m_position.y - m_animation.GetFrameSize().y / TILE_SCALE;
}

bool Entity::IsColliding(Entity* _other)
{
	sf::FloatRect tmp = GetHitbox();
	tmp.width /= TILE_SCALE;
	tmp.height /= TILE_SCALE;

	sf::FloatRect otherTmp = _other->GetHitbox();
	otherTmp.width /= TILE_SCALE;
	otherTmp.height /= TILE_SCALE;

	return tmp.intersects(otherTmp);
}