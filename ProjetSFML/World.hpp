#ifndef WORLD__HPP
#define WORLD__HPP

#define MAP_SIZE 250

#include "Common.hpp"
#include "Entity.hpp"
#include "Tile.hpp"

class World
{
private:
	std::list<Entity*> m_entities;

	Tile* m_tiles[MAP_SIZE][MAP_SIZE] = { nullptr };

public:
	World();
	~World();

	/// <summary>
	/// Updates the world every frame
	/// </summary>
	/// <param name="_dt">Time since the last frame (in seconds)</param>
 	void Update(float _dt);

	/// <summary>
	/// Draws the world to the screen
	/// </summary>
	/// <param name="_window">The window platform</param>
	/// <param name="_camera">The camera used by the game to render</param>
 	void Draw(sf::RenderWindow& _window, Camera _camera);

	/// <summary>
	/// Adds an entity to the world
	/// </summary>
	/// <param name="_entity">The entity to add</param>
	void SpawnEntity(Entity* _entity) { m_entities.push_back(_entity); }
};

#endif