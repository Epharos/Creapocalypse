#ifndef TEXT_RENDERER__HPP
#define TEXT_RENDERER__HPP

#include "Common.hpp"

struct Text
{
	std::string m_text;
	sf::Color m_color;
	sf::Text::Style m_style = sf::Text::Style::Regular;
};

class TextRenderer
{
private:
	sf::Font m_pixelFont;

public:
	TextRenderer();

	void RenderText(sf::RenderWindow& _window, std::string _text, sf::Vector2f _position, int _size, sf::Color _color);
	void RenderText(sf::RenderWindow& _window, std::string _text, sf::Vector2f _position, int _size, sf::Color _color, sf::Text::Style _style);

	void RenderText(sf::RenderWindow& _window, std::vector<Text> _texts, sf::Vector2f _position, int _size);

	void RenderTextMultiline(sf::RenderWindow& _window, std::string _text, sf::Vector2f _position, int _size, sf::Color _color, int _maxWidth);

	sf::Text CreateText(std::string _text, int _size, sf::Color _color);

	std::string FloatToString(float _value, int _precision = 2);
};

#endif