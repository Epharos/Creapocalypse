#ifndef TURRETTAB_HPP
#define TURRETTAB_HPP

#include "Widget.hpp"
#include "TurretSelection.hpp"
#include "BaseTurret.hpp"

class TurretTab : public Widget
{
protected:
	bool m_active = false;
	sf::Sprite m_turretSprite;
	TurretSelection* m_parent;
	BaseTurret* m_turret = nullptr;

public:
	TurretTab(sf::Vector2f _position, TurretSelection* _parent);
	~TurretTab();

	void SetTurretSprite(std::string _texture);
	void SetTurret(BaseTurret* _turret) { m_turret = _turret; }

	void Update(float _dt) override;
	void Draw(sf::RenderWindow& _window) override;
	void OnClick(sf::Vector2i _mousePos) override;

	void SetActive(bool _active) { m_active = _active; }
	bool IsActive() { return m_active; }

	BaseTurret* GetTurret() { return m_turret; }

	friend class TurretSelection;
};

#endif