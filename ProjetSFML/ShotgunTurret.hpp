#ifndef SHOTGUNTURRET_HPP
#define SHOTGUNTURRET_HPP

#include "BaseTurret.hpp"

class ShotgunTurret : public BaseTurret
{
private:
	Animation m_spawingAnimation;
	Animation m_shootingAnimation;

public:
	ShotgunTurret(sf::Vector2f _pos, float _rotation);

	virtual void Shoot() override;
	virtual bool IsTargetValid(Entity*& _target) override;
	virtual void AcquireTarget(World& _world) override;

	void Update(float _dt) override;
	void Draw(sf::RenderWindow& _window, Camera _camera) override;

	void SetPosition(sf::Vector2f& _pos) override;

	BaseTurret* Clone() override;
};

#endif