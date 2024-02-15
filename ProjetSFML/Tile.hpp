#ifndef TILE__HPP
#define TILE__HPP

#include "Common.hpp"
#include "Camera.hpp"

class Tile
{
protected:
	sf::Sprite m_sprite;

public:
	Tile(std::string _texturePath);
	~Tile() {};

	/// <summary>
	/// Draws the tile to the screen
	/// </summary>
	/// <param name="_window">The window that will render the tile</param>
	/// <param name="_camera">The camera used by the game</param>
	/// <param name="_i">x position of the tile</param>
	/// <param name="_j">y position of the tile</param>
	void Draw(sf::RenderWindow& _window, Camera _camera, int _i, int _j);

	/// <param name="_window">The window that will render the tile</param>
	/// <param name="_camera">The camera used by the game</param>
	/// <param name="_i">x position of the tile</param>
	/// <param name="_j">y position of the tile</param>
	/// <returns>Returns a bool whether the tile should be renderer or not</returns>
	bool ShouldBeRendered(Camera _camera, sf::RenderWindow& _window, int _i, int _j);

	static Tile* GRASS;
};

#endif