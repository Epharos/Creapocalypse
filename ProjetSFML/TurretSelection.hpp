#ifndef TURRETSELECTION_HPP
#define TURRETSELECTION_HPP

#include "BaseUI.hpp"

class TurretTab;

class TurretSelection : public BaseUI
{
protected:
	TurretTab* m_selectedTurret = nullptr;
public:
	TurretSelection();
	~TurretSelection();

	void Update(float _dt) override;
	void Draw(sf::RenderWindow& _window) override;
	void OnClick(sf::Vector2i _mousePos) override;

	TurretTab* GetSelectedTurret() { return m_selectedTurret; }

	friend class TurretTab;
};

#endif