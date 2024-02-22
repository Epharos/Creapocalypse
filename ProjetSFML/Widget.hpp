#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "BaseUI.hpp"

class Widget : public BaseUI
{
public:
	Widget(sf::Vector2f _position, sf::Vector2f _size, std::string _texture) : BaseUI(_position, _size, _texture) {};

	virtual void OnClick(sf::Vector2i _mousePos) override = 0;
};

#endif