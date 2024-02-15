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

public:
	Player(std::string _texturePath, sf::FloatRect _hitbox);

	virtual void Update(float _dt) override;
	virtual void Draw(sf::RenderWindow& _window, Camera _camera) override;
	virtual bool IsDead() override;
	virtual void Kill() override;
};

#endif