#include "GameManager.hpp"

#include "LMGTurret.hpp"
#include "Regular.hpp"

#include "TurretSelection.hpp"

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

	m_player->RealTimeKeyboardInput();
	m_player->RealTimeMouseInput(sf::Mouse::getPosition(m_window));

	m_world.Update(m_deltaTime);

	if (m_currentUI != nullptr)
	{
		m_currentUI->Update(m_deltaTime);
	}
}

void GameManager::Draw()
{
	m_window.clear();

	m_world.Draw(m_window, m_camera);

	if (m_debugMode)
	{
		m_textRenderer.RenderText(m_window, "FPS: " + std::to_string(static_cast<int>(1.f / m_deltaTime)), sf::Vector2f(10, 10), 16, sf::Color::Yellow);
		m_textRenderer.RenderText(m_window, "Camera position: " + std::to_string(m_camera.GetPosition().x) + ", " + std::to_string(m_camera.GetPosition().y), sf::Vector2f(10, 30), 16, sf::Color::Yellow);
		m_textRenderer.RenderText(m_window, "Entity count: " + std::to_string(m_world.GetEntities().size()), sf::Vector2f(10, 50), 16, sf::Color::Yellow);
		m_textRenderer.RenderText(m_window, "Bullet count: " + std::to_string(m_world.GetBullets().size()), sf::Vector2f(10, 70), 16, sf::Color::Yellow);
	}

	BlitSprite(heartSprite, sf::Vector2f(16, m_window.getSize().y - 48), 0.f, m_window);
	m_textRenderer.RenderText(m_window, m_textRenderer.FloatToString(m_player->GetHealth(), 1), sf::Vector2f(48, m_window.getSize().y - 48), 16, sf::Color::White);
	BlitSprite(diamantumSprite, sf::Vector2f(16, m_window.getSize().y - 80), 0.f, m_window);
	m_textRenderer.RenderText(m_window, m_textRenderer.FloatToString(m_player->GetMoney(), 1), sf::Vector2f(48, m_window.getSize().y - 80), 16, sf::Color::White);

	if (m_currentUI != nullptr)
	{
		sf::RectangleShape background(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));
		background.setFillColor(sf::Color(0, 0, 0, 100));
		m_window.draw(background);

		m_currentUI->Draw(m_window);
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
				m_player->EventKeyboardInput(event.key.code, event.key);

				if (event.key.code == sf::Keyboard::Escape)
				{
					if (m_currentUI != nullptr)
					{
						CloseUI();
					}
					else
					{
						m_window.close();
					}
				}

				if (event.key.code == sf::Keyboard::F1)
				{
					m_debugMode = !m_debugMode;
					std::cout << "Debug mode: " << (m_debugMode ? "ON" : "OFF") << std::endl;
				}

				if (event.key.code == sf::Keyboard::F2)
				{
					m_player->Hurt(10);
				}
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				m_player->EventMouseInput(event.mouseButton.button, sf::Mouse::getPosition(m_window));

				if (m_currentUI != nullptr)
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
					m_currentUI->OnClick(mousePos);
				}
			}
		}

		Update();
		Draw();
	}
}

void GameManager::CloseUI()
{
	if (m_currentUI != nullptr)
	{
		delete m_currentUI;
		m_currentUI = nullptr;
	}
}

void GameManager::OpenUI(BaseUI* _ui)
{
	CloseUI();

	m_currentUI = _ui;
}