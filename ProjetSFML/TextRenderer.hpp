#ifndef TEXT_RENDERER__HPP
#define TEXT_RENDERER__HPP

#include "Common.hpp"

class TextRenderer
{
private:
	sf::Font m_pixelFont;

public:
	TextRenderer();

	void RenderText(sf::RenderWindow& _window, std::string _text, sf::Vector2f _position, int _size, sf::Color _color);
};

#endif