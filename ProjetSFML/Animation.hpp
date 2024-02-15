#ifndef ANIMATION__HPP
#define ANIMATION__HPP

#include "Common.hpp"

class Animation
{
private:
	sf::Sprite m_sprite;
	sf::Vector2i m_frameSize;
	int m_numFrames;
	int m_currentFrame;
	float m_duration;
	float m_elapsedTime;

public:
	Animation(const std::string _path, sf::Vector2i _frameSize, int _numFrames, float _duration);
	~Animation();

	/// <summary>
	/// Updates the animation every frame
	/// </summary>
	/// <param name="_dt">Time since the last frame (in seconds)</param>
	void Update(float _dt);

	/// <summary>
	/// Draws the animation to the screen
	/// </summary>
	/// <param name="_window">The window platform</param>
	/// <param name="_pos">The position of the animation</param>
	/// <param name="_angle">The angle of the animation</param>
	void Draw(sf::RenderWindow& _window, sf::Vector2f _pos, float _angle);

	/// <summary>
	/// Resets the animation to the first frame
	/// </summary>
	void Reset();

	/// <returns>Returns the size of the frame</returns>
	sf::Vector2i GetFrameSize() const { return m_frameSize; }
};

#endif