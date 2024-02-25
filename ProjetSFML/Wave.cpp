#include "Wave.hpp"
#include "GameManager.hpp"

#include "Regular.hpp"

void Wave::Update(float deltaTime)
{
	m_internalTimer += deltaTime;

	if (!m_waveActive && m_internalTimer >= WAVE_PREPARE_TIME)
	{
		m_waveActive = true;
		SpawnWave(GameManager::GetInstance()->GetWorld());
	}
}

void Wave::Render(sf::RenderWindow& window)
{
	TextRenderer tr = GameManager::GetInstance()->GetTextRenderer();

	if (!m_waveActive)
	{
		tr.RenderText(window, {
			{ "Wave ", sf::Color::White },
			{ "#" + std::to_string(m_waveNumber), sf::Color(255, 50, 50)},
			{ " in ", sf::Color::White },
			{ tr.FloatToString(WAVE_PREPARE_TIME - m_internalTimer, 0), sf::Color(255, 50, 50)},
			{ " seconds", sf::Color::White } },
			sf::Vector2f(16, window.getSize().y - 32), 16);
	}
}

void Wave::SpawnWave(World& _world)
{
	for (int i = 0; i < m_waveSize; i++)
	{
		Regular* enemy = new Regular(sf::Vector2f((rand() / (float)RAND_MAX) * MAP_SIZE, (rand() / (float)RAND_MAX) * MAP_SIZE), "player_walk");
		_world.SpawnEntity(enemy);
		m_enemies.push_back(enemy);
	}
}

bool Wave::IsWaveComplete() const
{
	for (auto enemy : m_enemies)
	{
		if (!enemy->IsDead())
		{
			return false;
		}
	}

	return true;
}

Wave* Wave::CreateNextWave()
{
	return new Wave(m_waveNumber + 1, m_waveSize + rand() % 4 + 1);
}