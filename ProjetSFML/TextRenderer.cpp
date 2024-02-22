#include "TextRenderer.hpp"
#include <sstream>
#include <iomanip>

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

void TextRenderer::RenderText(sf::RenderWindow& _window, std::string _text, sf::Vector2f _position, int _size, sf::Color _color, sf::Text::Style _style)
{
	sf::Text text;
	text.setFont(m_pixelFont);
	text.setString(_text);
	text.setCharacterSize(_size);
	text.setFillColor(_color);
	text.setStyle(_style);
	text.setPosition(_position);

	_window.draw(text);
}

void TextRenderer::RenderText(sf::RenderWindow& _window, std::vector<Text> _texts, sf::Vector2f _position, int _size)
{
	float prevTextSize = 0.f;

	for (int i = 0; i < _texts.size(); i++)
	{
		sf::Text text;
		text.setFont(m_pixelFont);
		text.setString(_texts[i].m_text);
		text.setCharacterSize(_size);
		text.setFillColor(_texts[i].m_color);
		text.setPosition(_position.x + prevTextSize, _position.y);
		text.setStyle(_texts[i].m_style);
		prevTextSize += text.getLocalBounds().width;

		_window.draw(text);
	}
}

void TextRenderer::RenderTextMultiline(sf::RenderWindow& _window, std::string _text, sf::Vector2f _position, int _size, sf::Color _color, int _maxWidth)
{
	std::vector<std::string> words;
	std::string currentWord = "";

	for (int i = 0; i < _text.size(); i++)
	{
		if (_text[i] == ' ')
		{
			words.push_back(currentWord);
			currentWord = "";
		}
		else
		{
			currentWord += _text[i];
		}
	}

	words.push_back(currentWord);

	std::string currentLine = "";
	std::vector<std::string> lines;

	for (int i = 0; i < words.size(); i++)
	{
		if (currentLine.size() + words[i].size() < _maxWidth)
		{
			currentLine += words[i] + " ";
		}
		else
		{
			lines.push_back(currentLine);
			currentLine = words[i] + " ";
		}
	}

	lines.push_back(currentLine);

	for (int i = 0; i < lines.size(); i++)
	{
		RenderText(_window, lines[i], sf::Vector2f(_position.x, _position.y + (i * (_size + 3))), _size, _color);
	}
}

std::string TextRenderer::FloatToString(float _value, int _precision)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(_precision) << _value;
	return stream.str();
}