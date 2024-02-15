#include "Camera.hpp"

sf::Vector2f Camera::WorldToScreen(sf::Vector2f _worldPos)
{
	return (_worldPos - m_position) * static_cast<float>(TILE_SCALE);
}

sf::Vector2f Camera::ScreenToWorld(sf::Vector2f _screenPos)
{
	return (_screenPos + m_position) * static_cast<float>(TILE_SCALE);
}

void Camera::Move(sf::Vector2f _direction, float _dt)
{
	m_position += _direction * CAMERA_SPEED * _dt;
}