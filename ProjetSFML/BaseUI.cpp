#include "BaseUI.hpp"
#include "Widget.hpp"
#include "GameManager.hpp"

BaseUI::~BaseUI()
{
	for (auto& widget : m_widgets)
	{
		delete widget;
	}

	m_widgets.clear();
}

void BaseUI::Update(float _dt)
{
	for (auto& widget : m_widgets)
	{
		widget->Update(_dt);
	}

	if(IsHovered(sf::Mouse::getPosition(GameManager::GetInstance()->GetWindow())))
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			OnClick(sf::Mouse::getPosition(GameManager::GetInstance()->GetWindow()));
		}
	}
}

void BaseUI::Draw(sf::RenderWindow& _window)
{
	_window.draw(m_background);

	for (auto& widget : m_widgets)
	{
		if (widget->IsVisible())
		{
			widget->Draw(_window);
		}
	}
}

void BaseUI::OnClick(sf::Vector2i _mousePos)
{
	
}

void BaseUI::AddWidget(Widget* _widget)
{
	m_widgets.push_back(_widget);
}

bool BaseUI::IsHovered(sf::Vector2i _mousePos)
{
	sf::FloatRect bounds = sf::FloatRect(m_position, m_size);
	return bounds.contains(static_cast<sf::Vector2f>(_mousePos));
}