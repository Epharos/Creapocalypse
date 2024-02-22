#ifndef BASEUI_HPP
#define BASEUI_HPP

#include "Common.hpp"
#include "TextureManager.hpp"

class Widget;

class BaseUI
{
protected:
	sf::Vector2f m_position;
	sf::Vector2f m_size;

	sf::Sprite m_background;
	std::list<Widget*> m_widgets;

public:
	BaseUI(sf::Vector2f _position, sf::Vector2f _size, std::string _texture) : m_position(_position), m_size(_size)
	{
		m_background.setTexture(*TextureManager::GetTexture(_texture));
		m_background.setPosition(m_position);
	}

	virtual void Update(float _dt);
	virtual void Draw(sf::RenderWindow& _window);
	virtual void OnClick(sf::Vector2i _mousePos);

	void AddWidget(Widget* _widget);

	void Close();

	bool IsHovered(sf::Vector2i _mousePos) { return m_background.getGlobalBounds().contains((sf::Vector2f)_mousePos); }

	std::list<Widget*>& GetWidgets() { return m_widgets; }
};

#endif