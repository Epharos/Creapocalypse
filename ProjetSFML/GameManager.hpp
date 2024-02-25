#ifndef GAME_MANAGER__HPP
#define GAME_MANAGER__HPP

#include "Common.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Player.hpp"
#include "TextRenderer.hpp"
#include "BaseUI.hpp"

#include "Wave.hpp"

class GameManager
{
private:
    sf::RenderWindow m_window;
    World m_world;
    Camera m_camera;
    Player* m_player;
    BaseUI* m_currentUI = nullptr;

    sf::Clock m_clock;
    float m_deltaTime;

    bool m_debugMode = false;

    Wave* m_currentWave;

    TextRenderer m_textRenderer;

    static GameManager* _INSTANCE;

    sf::Sprite heartSprite;
    sf::Sprite diamantumSprite;

    GameManager() : 
        m_window(sf::VideoMode(1920, 1080), "Creapocalypse"), m_world(), m_camera(), m_clock(),
        m_deltaTime(.0f), m_player(new Player("player", sf::FloatRect(0.f, 0.f, 32.f, 64.f)))
    {
        m_world.SpawnEntity(m_player);
        heartSprite = LoadSprite("assets/ui/heart.png", false);
        diamantumSprite = LoadSprite("assets/ui/diamantum.png", false);
        m_currentWave = new Wave(1, 10);
    };

public:
    /// <summary>
    /// Singleton ->
    /// Returns the instance of the GameManager or creates it if it doesn't exist
    /// </summary>
    /// <returns>The adress of the GameManager's singleton</returns>
    static GameManager* GetInstance();

    sf::RenderWindow& GetWindow() { return m_window; }
    World& GetWorld() { return m_world; }
    Camera& GetCamera() { return m_camera; }
    Player*& GetPlayer() { return m_player; }
    BaseUI*& GetCurrentUI() { return m_currentUI; }
    bool GetDebugMode() { return m_debugMode; }
    TextRenderer& GetTextRenderer() { return m_textRenderer; }

    /// <summary>
    /// Close the current opened UI
    /// </summary>
    void CloseUI();

    /// <summary>
    /// Close the current opened UI (if any) and then open a new UI
    /// </summary>
    /// <param name="_ui">The UI to open</param>
    void OpenUI(BaseUI* _ui);

    /// <summary>
    /// Updates the game every frame
    /// </summary>
    void Update();

    /// <summary>
    /// Draws the game to the screen
    /// </summary>
    void Draw();

    /// <summary>
    /// Handles the game loop
    /// </summary>
    void Run();
};

#endif