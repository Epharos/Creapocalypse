#include "World.hpp"
#include "House.hpp"
#include "Garage.hpp"
#include "Hangar.hpp"
#include "Pigfarm.hpp"
#include "Barn.hpp"
#include "GameManager.hpp"

#include "BaseTurret.hpp"

#include "Bullet.hpp"

#include <ranges>

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

	// Add buildings to the world
	SpawnBuildings();
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
	//TODO : modifier le remove_if pour delete les entités mortes
	m_entities.remove_if([](Entity* _entity) { return _entity->IsDead(); });
	m_bullets.remove_if([](Bullet* _bullet) { return _bullet->IsDead(); });

	// Update all the entities
	for (auto& entity : m_entities)
	{
		entity->Update(_deltaTime);
	}

	// Update all the bullets
	for (auto& bullet : m_bullets)
	{
		bullet->Update(_deltaTime);
	}

	//TODO : retirer les std::views::filter et std::ranges::for_each
	auto turrets = m_entities |
		std::views::filter([](Entity* _entity) { return IsTurret(_entity); });

	std::ranges::for_each(turrets, [](Entity* _entity) { 
		BaseTurret* t = dynamic_cast<BaseTurret*>(_entity);
		
		if (t->GetTarget() != nullptr && t->GetTarget()->IsDead())
		{
			t->SetTarget(nullptr);
		}
	});
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

	// Draw all the bullets
	for (auto& bullet : m_bullets)
	{
		bullet->Draw(_window, _camera);
	}
}

void World::SpawnEntity(Entity* _entity)
{
	if (IsBullet(_entity))
	{
		m_bullets.push_back(dynamic_cast<Bullet*>(_entity));
	}
	else
	{
		m_entities.push_back(_entity);
	}
}

void World::SpawnEntity(Entity* _entity, sf::Vector2f _position)
{
	_entity->SetPosition(_position);
	SpawnEntity(_entity);
}

bool World::SpawnEntityAtRandomLocation(Entity* _entity, sf::Vector2f _position)
{
	_entity->SetPosition(_position);

	for (auto& entity : m_entities)
	{
		if (entity != _entity)
		{
			if (entity->IsColliding(_entity))
			{
				return false;
			}
		}
	}

	SpawnEntity(_entity);
	return true;
}

/// <summary>
/// Adds the buildings to the world
/// </summary>
/// <param name="_world">World to spawn the buildings in</param>
void World::SpawnBuildings()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(MAP_SIZE / 2 - MAP_SIZE / 4, MAP_SIZE / 2 + MAP_SIZE / 4);

	// Add buildings to the world
	House* house = new House();
	sf::Vector2f position = sf::Vector2f(dist(gen), dist(gen));

	while (!SpawnEntityAtRandomLocation(house, position))
	{
		position = sf::Vector2f(dist(gen), dist(gen));
	}

	std::cout << "House position: " << position.x << " " << position.y << std::endl;

	Garage* garage = new Garage();
	position = sf::Vector2f(dist(gen), dist(gen));

	while (!SpawnEntityAtRandomLocation(garage, position))
	{
		position = sf::Vector2f(dist(gen), dist(gen));
	}

	std::cout << "Garage position: " << position.x << " " << position.y << std::endl;

	Hangar* hangar = new Hangar();
	position = sf::Vector2f(dist(gen), dist(gen));

	while (!SpawnEntityAtRandomLocation(hangar, position))
	{
		position = sf::Vector2f(dist(gen), dist(gen));
	}

	std::cout << "Hangar position: " << position.x << " " << position.y << std::endl;

	Pigfarm* pigfarm = new Pigfarm();
	position = sf::Vector2f(dist(gen), dist(gen));

	while (!SpawnEntityAtRandomLocation(pigfarm, position))
	{
		position = sf::Vector2f(dist(gen), dist(gen));
	}

	std::cout << "Pigfarm position: " << position.x << " " << position.y << std::endl;

	Barn* barn = new Barn();
	position = sf::Vector2f(dist(gen), dist(gen));

	while (!SpawnEntityAtRandomLocation(barn, position))
	{
		position = sf::Vector2f(dist(gen), dist(gen));
	}

	std::cout << "Barn position: " << position.x << " " << position.y << std::endl;
}