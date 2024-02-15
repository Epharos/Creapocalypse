#include "Entity.hpp"

Entity::Entity(std::string _texturePath, sf::FloatRect _hitbox) : 
	m_position(0, 0), m_hitbox(_hitbox), m_yaw(0.f), m_animation(_texturePath, sf::Vector2i(32, 64), 1, 0.1f)
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

	m_animation.Draw(_window, _camera.WorldToScreen(m_position), m_yaw);
}

bool Entity::ShouldBeRendered(Camera _camera, sf::RenderWindow& _window)
{
	sf::Vector2f screenPos = _camera.WorldToScreen(m_position);
	sf::Vector2i size = m_animation.GetFrameSize();

	return screenPos.x + size.x / 2 > 0 && screenPos.x - size.x / 2 < _window.getSize().x && screenPos.y + size.y > 0 && screenPos.y < _window.getSize().y + size.y;
}