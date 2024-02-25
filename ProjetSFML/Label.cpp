#include "Label.hpp"
#include "GameManager.hpp"

Label::Label(sf::Vector2f _position, std::string _text, OnClickCallback _callback)
{
	m_position = _position;
	m_textObject = GameManager::GetInstance()->GetTextRenderer().CreateText(_text, 24, sf::Color::White);
	m_size = sf::Vector2f(m_textObject.getGlobalBounds().width, m_textObject.getGlobalBounds().height);
	m_text = _text;
	m_callback = _callback;
}

void Label::Draw(sf::RenderWindow& _window)
{
	TextRenderer tr = GameManager::GetInstance()->GetTextRenderer();

	tr.RenderText(_window, m_text, m_position, 24, IsHovered(sf::Mouse::getPosition(_window)) ? sf::Color::Green : sf::Color::White);
}

void Label::OnClick(sf::Vector2i _mousePos)
{
	if (m_callback != nullptr)
	{
		m_callback();
	}
}