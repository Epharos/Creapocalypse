#include "TurretSelection.hpp"
#include "GameManager.hpp"
#include "TurretSelector.hpp"

#include "LMGTurret.hpp"

TurretSelection::TurretSelection() : BaseUI(sf::Vector2f(GameManager::GetInstance()->GetWindow().getSize().x / 2 - 384
	, GameManager::GetInstance()->GetWindow().getSize().y / 2 - 388), sf::Vector2f(768, 576), "turretScreen")
{
	TurretSelector* lmgSelector = new TurretSelector(sf::Vector2f(this->m_position.x + 10, this->m_position.y + this->m_size.y), this);
	lmgSelector->SetTurretSprite("lmg");
	lmgSelector->SetTurret(new LightMachineGunTurret(sf::Vector2f(0, 0), 0.f));
	lmgSelector->m_active = true;
	AddWidget(lmgSelector);
}

TurretSelection::~TurretSelection()
{
}

void TurretSelection::Update(float _dt)
{
	BaseUI::Update(_dt);
}

void TurretSelection::Draw(sf::RenderWindow& _window)
{
	BaseUI::Draw(_window);

	TextRenderer textRenderer = GameManager::GetInstance()->GetTextRenderer();
	textRenderer.RenderText(_window, "Turret Selection", sf::Vector2f(m_position.x + 20, m_position.y + 20), 24, sf::Color::White, sf::Text::Style::Bold);

	if (m_selectedTurret != nullptr)
	{
		textRenderer.RenderText(_window, m_selectedTurret->m_turret->GetName(), sf::Vector2f(m_position.x + 30, m_position.y + 65), 24, sf::Color::Cyan);
		
		textRenderer.RenderText(_window, {
			{ "Damages: ", sf::Color::White },
			{ textRenderer.FloatToString(m_selectedTurret->m_turret->GetBulletDamage(), 1), sf::Color::Yellow }
			}, sf::Vector2f(m_position.x + 30, m_position.y + 98), 16);

		textRenderer.RenderText(_window, {
			{ "Fire rate: ", sf::Color::White },
			{ textRenderer.FloatToString(m_selectedTurret->m_turret->GetFireRate(), 1), sf::Color::Yellow },
			{ " bullets per second", sf::Color::White }
			}, sf::Vector2f(m_position.x + 30, m_position.y + 131), 16);

		textRenderer.RenderText(_window, {
			{ "Spotting range: ", sf::Color::White },
			{ textRenderer.FloatToString(m_selectedTurret->m_turret->GetRange(), 1), sf::Color::Yellow},
			{ " meters", sf::Color::White }
			}, sf::Vector2f(m_position.x + 30, m_position.y + 156), 16);

		textRenderer.RenderText(_window, {
			{ "Spread: ", sf::Color::White },
			{ textRenderer.FloatToString(ToDegrees(m_selectedTurret->m_turret->GetSpread()), 1), sf::Color::Yellow },
			{ " degrees", sf::Color::White }
			}, sf::Vector2f(m_position.x + 30, m_position.y + 181), 16);

		textRenderer.RenderText(_window, {
			{ "Bullet speed: ", sf::Color::White },
			{ textRenderer.FloatToString(m_selectedTurret->m_turret->GetBulletSpeed(), 1), sf::Color::Yellow },
			{ " m/s", sf::Color::White }
			}, sf::Vector2f(m_position.x + 30, m_position.y + 209), 16);

		textRenderer.RenderText(_window, {
			{ "Bullet range: ", sf::Color::White },
			{ textRenderer.FloatToString(m_selectedTurret->m_turret->GetBulletRange(), 1), sf::Color::Yellow},
			{ " meters", sf::Color::White }
			}, sf::Vector2f(m_position.x + 30, m_position.y + 234), 16);

		textRenderer.RenderText(_window, {
			{ "Cost: ", sf::Color::White },
			{ textRenderer.FloatToString(m_selectedTurret->m_turret->GetCost(), 1), sf::Color::Yellow },
			{ " $", sf::Color::White }
			}, sf::Vector2f(m_position.x + 30, m_position.y + m_size.y - 30), 16);

		/*textRenderer.RenderText(_window, {
			{ "Description: ", sf::Color::White },
			{ m_selectedTurret->m_turret->GetDescription(), sf::Color::Yellow }
			}, sf::Vector2f(m_position.x + 30, m_position.y + 198), 16);*/

		textRenderer.RenderTextMultiline(_window, m_selectedTurret->m_turret->GetDescription(), sf::Vector2f(m_position.x + 30, m_position.y + 264), 16, sf::Color::Yellow, 35);
	}
}

void TurretSelection::OnClick(sf::Vector2i _mousePos)
{
	BaseUI::OnClick(_mousePos);
}