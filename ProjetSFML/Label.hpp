#ifndef LABEL_HPP
#define LABEL_HPP

#include "Widget.hpp"

typedef void(*OnClickCallback)(void);

class Label : public Widget
{
protected:
	OnClickCallback m_callback;
	std::string m_text;
	sf::Text m_textObject;

public:
	Label(sf::Vector2f _position, std::string _text, OnClickCallback _callback = nullptr);

	void SetText(std::string _text) { m_text = _text; }
	std::string GetText() { return m_text; }

	void SetCallback(OnClickCallback _callback) { m_callback = _callback; }

	void Draw(sf::RenderWindow& _window) override;
	void OnClick(sf::Vector2i _mousePos) override;
};

#endif