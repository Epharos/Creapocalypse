#ifndef BUlLET_HPP
#define BULLET_HPP

#include "LivingEntity.hpp"

class Bullet : public LivingEntity
{
protected:
	float m_damage;
	float m_range;

public:
	Bullet(sf::Vector2f _pos, float _rotation, float _speed, float _damage, float _range, std::string _texturePath);
	~Bullet();

	void Update(float _dt) override;

	bool IsDead() override;
	void Kill() override;

	bool IsColliding(Entity* _other) override;
	bool CanCollideWith(Entity*& _other) override;
	void OnCollide(Entity*& _other) override;
};

#endif