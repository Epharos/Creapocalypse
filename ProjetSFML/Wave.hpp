#ifndef WAVE_HPP
#define WAVE_HPP

#include "Common.hpp"
#include "Enemy.hpp"

#define WAVE_PREPARE_TIME 25.0f // 25 seconds to prepare for the wave

class Wave
{
private:
	float m_internalTimer;
	UINT m_waveNumber;
	UINT m_waveSize;

	std::list<Enemy*> m_enemies;

	bool m_waveActive;

public:
	Wave(UINT _waveNumber, UINT _waveSize) : m_waveNumber(_waveNumber), m_waveSize(_waveSize), m_internalTimer(0.0f), m_waveActive(false) { }
	~Wave() { }

	void Update(float _dt);
	void Render(sf::RenderWindow& _window);

	void SpawnWave(World& _world);
	bool IsWaveActive() const { return m_waveActive; }
	bool IsWaveComplete() const;

	Wave* CreateNextWave();
};

#endif