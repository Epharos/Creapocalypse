#include "TextRenderer.hpp"

TextRenderer::TextRenderer()
{
	m_pixelFont.loadFromFile("assets/pixelmix.ttf");
}

void TextRenderer::RenderText(sf::RenderWindow& _window, std::string _text, sf::Vector2f _position, int _size, sf::Color _color)
{
	sf::Text text;
	text.setFont(m_pixelFont);
	text.setString(_text);
	text.setCharacterSize(_size);
	text.setFillColor(_color);
	text.setPosition(_position);

	_window.draw(text);
}