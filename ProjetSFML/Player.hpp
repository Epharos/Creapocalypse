#ifndef PLAYER__HPP
#define PLAYER__HPP

#include "LivingEntity.hpp"

class BaseTurret;

enum PlayerState
{
	Idle,
	Moving,
	Crafting,
	Placing
};

class Player : public LivingEntity
{
private:
	Animation m_walkingAnimation;

	PlayerState m_state;

	sf::Vector2f m_targetPosition;

	float m_money;
	BaseTurret* m_placingTurret = nullptr;

public:
	Player(std::string _texturePath, sf::FloatRect _hitbox);

	virtual void Update(float _dt) override;
	virtual void Draw(sf::RenderWindow& _window, Camera _camera) override;

	void RealTimeKeyboardInput();
	void RealTimeMouseInput(sf::Vector2i _mousePos);

	void EventKeyboardInput(sf::Keyboard::Key _key, sf::Event::KeyEvent _event);
	void EventMouseInput(sf::Mouse::Button _button, sf::Vector2i _mousePos);

	float& GetMoney() { return m_money; }
	BaseTurret* GetPlacingTurret() { return m_placingTurret; }
	void SetPlacingTurret(BaseTurret* _turret) { m_placingTurret = _turret; }

	void SetState(PlayerState _state) { m_state = _state; }
	PlayerState GetState() { return m_state; }
};

#endif