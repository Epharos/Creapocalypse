#ifndef TURRETSELECTION_HPP
#define TURRETSELECTION_HPP

#include "BaseUI.hpp"

class TurretSelector;

class TurretSelection : public BaseUI
{
protected:
	TurretSelector* m_selectedTurret = nullptr;
public:
	TurretSelection();
	~TurretSelection();

	void Update(float _dt) override;
	void Draw(sf::RenderWindow& _window) override;
	void OnClick(sf::Vector2i _mousePos) override;

	TurretSelector* GetSelectedTurret() { return m_selectedTurret; }

	friend class TurretSelector;
};

#endif