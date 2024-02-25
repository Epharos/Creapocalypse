#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "BaseUI.hpp"

class Widget : public BaseUI
{
protected:
	bool m_visible = true;

public:
	Widget() : BaseUI(sf::Vector2f(0, 0), sf::Vector2f(0, 0), "") {};
	Widget(sf::Vector2f _position, sf::Vector2f _size, std::string _texture) : BaseUI(_position, _size, _texture) {};

	virtual void OnClick(sf::Vector2i _mousePos) override = 0;

	void SetVisible(bool _visible) { m_visible = _visible; }
	bool IsVisible() { return m_visible; }
};

#endif