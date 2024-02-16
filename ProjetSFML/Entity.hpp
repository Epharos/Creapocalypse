#ifndef ENTITY__HPP
#define ENTITY__HPP

#include "Common.hpp"
#include "Camera.hpp"
#include "Animation.hpp"

class Entity
{
protected:
	sf::Vector2f m_position;
	float m_yaw;
	float m_speed;

	Animation m_animation;
	sf::FloatRect m_hitbox;

public:
	Entity(std::string _texturePath, sf::FloatRect _hitbox);
	virtual ~Entity() {};

	/// <summary>
	/// Updates the entity every frame
	/// </summary>
	/// <param name="_dt">Time since the last frame (in seconds)</param>
	virtual void Update(float _dt);

	/// <summary>
	/// Draws the entity to the screen
	/// </summary>
	/// <param name="_window">The window platform</param>
	/// <param name="_camera">The camera used by the game to render </param>
	virtual void Draw(sf::RenderWindow& _window, Camera _camera);

	/// <returns>Returns if the entity is dead or not</returns>
	virtual bool IsDead() = 0;

	/// <summary>
	/// Kills the entity (ie. sets it to a dead state)
	/// </summary>
	virtual void Kill() = 0;

	/// <summary>
	/// Set the position and the hitbox of the entity
	/// </summary>
	/// <param name="_pos"></param>
	virtual void SetPosition(sf::Vector2f& _pos);
	void SetYaw(float _yaw) { m_yaw = _yaw; }
	void SetSpeed(float _speed) { m_speed = _speed; }

	sf::Vector2f GetPosition() const { return m_position; }
	float GetYaw() const { return m_yaw; }
	float GetSpeed() const { return m_speed; }
	sf::FloatRect GetHitbox() const { return m_hitbox; }
	Animation GetAnimation() const { return m_animation; }

	/// <param name="_camera">The camera used by the game to render</param>
	/// <param name="_window">The window plateform</param>
	/// <returns>Returns if the entity should be rendered or not</returns>
	bool ShouldBeRendered(Camera _camera, sf::RenderWindow& _window);

	virtual bool IsColliding(Entity* _other);
};

#endif