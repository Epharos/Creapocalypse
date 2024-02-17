#ifndef LIGHTMACHINEGUNTURRET_HPP
#define LIGHTMACHINEGUNTURRET_HPP

#include "BaseTurret.hpp"

class LightMachineGunTurret : public BaseTurret
{
public:
	LightMachineGunTurret(sf::Vector2f _pos, float _rotation);

	virtual void Shoot() override;
	virtual bool IsTargetValid(Entity*& _target) override;
	virtual void AcquireTarget(World& _world) override;
};

#endif