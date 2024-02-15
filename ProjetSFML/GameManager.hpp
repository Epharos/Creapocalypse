#ifndef GAME_MANAGER__HPP
#define GAME_MANAGER__HPP

#include "Common.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Player.hpp"

class GameManager
{
private:
    sf::RenderWindow m_window;
    World m_world;
    Camera m_camera;
    Player* m_player;

    sf::Clock m_clock;
    float m_deltaTime;

    bool m_debugMode = false;

    //--- TO DELETE AFTER TESTING ---//
    sf::Font font;
    sf::Text fpsCounter;
    //-------------------------------//

    static GameManager* _INSTANCE;

    GameManager() : 
        m_window(sf::VideoMode(1024, 768), "Creapocalypse"), m_world(), m_camera(), m_clock(),
        m_deltaTime(.0f), m_player(new Player("assets/player/idle.png", sf::FloatRect(0.f, 0.f, 32.f, 64.f)))
    {
        m_world.SpawnEntity(m_player);

        //--- TO DELETE AFTER TESTING ---//
        font.loadFromFile("arial.ttf");

        fpsCounter.setFont(font);
        fpsCounter.setCharacterSize(24);
        fpsCounter.setFillColor(sf::Color::Yellow);
        fpsCounter.setPosition(10, 10);
        //-------------------------------//
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