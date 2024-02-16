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

	void SpawnBuildings();

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
	void SpawnEntity(Entity* _entity);

	/// <summary>
	/// Sets entity position and then adds it to the world
	/// </summary>
	/// <param name="_entity">The entity to add</param>
	/// <param name="_position">The spawn position of the entity</param>
	void SpawnEntity(Entity* _entity, sf::Vector2f _position);

	/// <summary>
	/// Tries to spawn an entity at a random position, checking for collisions
	/// </summary>
	/// <param name="_entity">The entity to add</param>
	/// <param name="_position">The spawn position of the entity</param>
	/// <returns>True if the entity was spawned, false otherwise</returns>
	bool SpawnEntityAtRandomLocation(Entity* _entity, sf::Vector2f _position);
};

#endif