#include "Tile.hpp"

Tile* Tile::GRASS = new Tile("assets/grass.png");

Tile::Tile(std::string _texturePath)
{
	sf::Texture* tmpTexture = new sf::Texture();
	tmpTexture->loadFromFile(_texturePath);

	m_sprite.setTexture(*tmpTexture);
	m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y);
}

void Tile::Draw(sf::RenderWindow& _window, Camera _camera, int _i, int _j)
{
	if (!ShouldBeRendered(_camera, _window, _i, _j))
	{
		return;
	}

	m_sprite.setPosition(_camera.WorldToScreen(sf::Vector2f(_i, _j)));
	_window.draw(m_sprite);
}

bool Tile::ShouldBeRendered(Camera _camera, sf::RenderWindow& _window, int _i, int _j)
{
	sf::Vector2f tempPos = _camera.WorldToScreen(sf::Vector2f(_i, _j));
	return tempPos.x > -TILE_SCALE / 2 && tempPos.x < _window.getSize().x + TILE_SCALE / 2 && tempPos.y > 0 && tempPos.y < _window.getSize().y + TILE_SCALE;
}