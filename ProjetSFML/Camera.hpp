#ifndef CAMERA__HPP
#define CAMERA__HPP

#define CAMERA_SPEED 20.0f

#include "Common.hpp"

class Camera
{
private:
	sf::Vector2f m_position;

public:
	Camera() : m_position({ 0, 0 }) {};
	~Camera() {};

	void SetPosition(sf::Vector2f& _pos) { m_position = _pos; };
	sf::Vector2f GetPosition() const { return m_position; };

	/// <summary>
	/// Transforms a world position to a screen position
	/// </summary>
	/// <param name="_worldPos">World position of the thing we want to get the screen position of</param>
	/// <returns>Returns a sf::Vector2f of where on screen should be the thing we want to render (for example)</returns>
	sf::Vector2f WorldToScreen(sf::Vector2f _worldPos);

	/// <summary>
	/// Transforms a screen position to a world position
	/// </summary>
	/// <param name="_screenPos">Screen position of the thing we want to get the world position of</param>
	/// <returns>Returns a sf::Vector2f of the position in the world of a click (for example)</returns>
	sf::Vector2f ScreenToWorld(sf::Vector2f _screenPos);

	/// <summary>
	/// Moves the camera in a given direction
	/// </summary>
	/// <param name="_direction">The direction in which the camera should move</param>
	/// <param name="_dt">Delta Time</param>
	void Move(sf::Vector2f _direction, float _dt);
};

#endif