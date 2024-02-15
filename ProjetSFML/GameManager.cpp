#include "GameManager.hpp"

GameManager* GameManager::_INSTANCE = nullptr;

GameManager* GameManager::GetInstance()
{
	if (_INSTANCE == nullptr)
	{
		_INSTANCE = new GameManager();
	}

	return _INSTANCE;
}

void GameManager::Update()
{
	m_deltaTime = m_clock.restart().asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		m_camera.Move(sf::Vector2f(0.f, -1.f), m_deltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_camera.Move(sf::Vector2f(0.f, 1.f), m_deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		m_camera.Move(sf::Vector2f(-1.f, 0.f), m_deltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_camera.Move(sf::Vector2f(1.f, 0.f), m_deltaTime);
	}

	m_world.Update(m_deltaTime);
}

void GameManager::Draw()
{
	m_window.clear();

	m_world.Draw(m_window, m_camera);

	if (m_debugMode)
	{
		fpsCounter.setString("FPS: " + std::to_string(static_cast<int>(1.f / m_deltaTime)));

		m_window.draw(fpsCounter);
	}

	m_window.display();
}

void GameManager::Run()
{
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					m_window.close();
				}

				if (event.key.code == sf::Keyboard::F1)
				{
					m_debugMode = !m_debugMode;
					std::cout << "Debug mode: " << (m_debugMode ? "ON" : "OFF") << std::endl;
				}
			}
		}

		Update();
		Draw();
	}
}