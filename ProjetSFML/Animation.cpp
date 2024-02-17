#include "Animation.hpp"

Animation::Animation(const std::string _path, sf::Vector2i _frameSize, int _numFrames, float _duration)
{
	m_sprite.setTexture(*TextureManager::GetTexture(_path));
	m_sprite.setOrigin(_frameSize.x / 2, _frameSize.y);
	m_frameSize = _frameSize;
	m_numFrames = _numFrames;
	m_duration = _duration;
	m_currentFrame = 0;
	m_elapsedTime = 0;
	m_once = false;
}

Animation::~Animation()
{
	//delete m_sprite.getTexture();
}

void Animation::Update(float _dt)
{
	m_elapsedTime += _dt;

	if (m_elapsedTime >= m_duration)
	{
		m_elapsedTime -= m_duration;
		m_currentFrame++;

		if (m_currentFrame >= m_numFrames && !m_once)
		{
			m_currentFrame = 0;
		}
	}
}

void Animation::Draw(sf::RenderWindow& _window, sf::Vector2f _pos, float _angle)
{
	sf::IntRect rectSourceSprite(m_currentFrame * m_frameSize.x, 0, m_frameSize.x, m_frameSize.y);
	m_sprite.setTextureRect(rectSourceSprite);
	m_sprite.setPosition(_pos);
	m_sprite.setScale(ToDegrees(_angle) > 90 && ToDegrees(_angle) < 270 ? 1 : -1, 1);
	_window.draw(m_sprite);
}

void Animation::Reset()
{
	m_currentFrame = 0;
	m_elapsedTime = 0;
}