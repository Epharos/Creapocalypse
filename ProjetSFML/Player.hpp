#ifndef PLAYER__HPP
#define PLAYER__HPP

#include "LivingEntity.hpp"

enum PlayerState
{
	Idle,
	Moving,
	Crafting
};

class Player : public LivingEntity
{
private:
	Animation m_walkingAnimation;

	PlayerState m_state;

	sf::Vector2f m_targetPosition;

	float m_money;

public:
	Player(std::string _texturePath, sf::FloatRect _hitbox);

	virtual void Update(float _dt) override;
	virtual void Draw(sf::RenderWindow& _window, Camera _camera) override;

	float& GetMoney() { return m_money; }
};

#endif