#include "BaseUI.hpp"
#include "Widget.hpp"
#include "GameManager.hpp"

void BaseUI::Update(float _dt)
{
	for (auto& widget : m_widgets)
	{
		widget->Update(_dt);
	}
}

void BaseUI::Draw(sf::RenderWindow& _window)
{
	_window.draw(m_background);

	for (auto& widget : m_widgets)
	{
		widget->Draw(_window);
	}
}

void BaseUI::OnClick(sf::Vector2i _mousePos)
{
	bool shouldClose = true;

	if (IsHovered(_mousePos))
	{
		shouldClose = false;
	}

	for (auto& widget : m_widgets)
	{
		if (widget->IsHovered(_mousePos))
		{
			shouldClose = false;
			widget->OnClick(_mousePos);
		}
	}

	if (shouldClose)
	{
		Close();
	}
}

void BaseUI::AddWidget(Widget* _widget)
{
	m_widgets.push_back(_widget);
}

void BaseUI::Close()
{
	for (auto& widget : m_widgets)
	{
		delete widget;
	}

	m_widgets.clear();
	delete this;
	GameManager::GetInstance()->GetCurrentUI() = nullptr;
	GameManager::GetInstance()->GetPlayer()->SetState(PlayerState::Idle);
}