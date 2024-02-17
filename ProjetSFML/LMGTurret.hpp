#ifndef LIGHTMACHINEGUNTURRET_HPP
#define LIGHTMACHINEGUNTURRET_HPP

#include "BaseTurret.hpp"

class LightMachineGunTurret : public BaseTurret
{
private:
	Animation m_spawingAnimation;
	Animation m_shootingAnimation;

public:
	LightMachineGunTurret(sf::Vector2f _pos, float _rotation);

	virtual void Shoot() override;
	virtual bool IsTargetValid(Entity*& _target) override;
	virtual void AcquireTarget(World& _world) override;

	void Update(float _dt) override;
	void Draw(sf::RenderWindow& _window, Camera _camera) override;

	void SetPosition(sf::Vector2f& _pos) override;
};

#endif