#include "World.hpp"

World::World()
{
	// Initialize the tiles
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			m_tiles[i][j] = Tile::GRASS;
		}
	}
}

World::~World()
{
	// Delete all the entities
	for (auto& entity : m_entities)
	{
		delete entity;
	}

	m_entities.clear();

	// Delete all the tiles
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			m_tiles[i][j] = nullptr;
		}
	}
}

void World::Update(float _deltaTime)
{
	// Update all the entities
	for (auto& entity : m_entities)
	{
		entity->Update(_deltaTime);
	}
}

void World::Draw(sf::RenderWindow& _window, Camera _camera)
{
	// Draw all the tiles
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			if (m_tiles[i][j] != nullptr)
			{
				m_tiles[i][j]->Draw(_window, _camera, i, j);
			}
		}
	}

	// Draw all the entities
	for (auto& entity : m_entities)
	{
		entity->Draw(_window, _camera);
	}
}