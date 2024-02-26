#ifndef REGULAR_HPP
#define REGULAR_HPP

#include "Enemy.hpp"

class Regular : public Enemy
{
protected:
	Animation m_movingAnimation;
	Animation m_attackingAnimation;
	Animation m_dyingAnimation;

public:
	Regular(sf::Vector2f _pos);
	~Regular();

	void AcquireTarget(World& _world) override;
	void Attack() override;
	bool IsTargetValid(Entity*& _target) override;

	bool IsDead() override;

	void Update(float _dt) override;
	void Draw(sf::RenderWindow& _window, Camera _camera) override;
};

#endif