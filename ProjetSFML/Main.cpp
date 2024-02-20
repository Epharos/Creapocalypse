#include "Common.hpp"
#include "GameManager.hpp"
#include "TextureManager.hpp"

int main()
{
    //Tiles
    TextureManager::LoadTexture("grass", "assets/grass.png");

    //Turrets
    TextureManager::LoadTexture("bullet", "assets/turrets/bullet.png");
    TextureManager::LoadTexture("lmg", "assets/turrets/lmg.png");
    TextureManager::LoadTexture("lmg_spawning", "assets/turrets/lmg_spawning.png");
    TextureManager::LoadTexture("lmg_firing", "assets/turrets/lmg_firing.png");

    //Entities
    TextureManager::LoadTexture("player", "assets/player/idle.png");
    TextureManager::LoadTexture("player_walk", "assets/player/moving.png");

    //Buildings
    TextureManager::LoadTexture("house", "assets/buildings/house.png");
    TextureManager::LoadTexture("barn", "assets/buildings/barn.png");
    TextureManager::LoadTexture("garage", "assets/buildings/garage.png");
    TextureManager::LoadTexture("hangar", "assets/buildings/hangar.png");
    TextureManager::LoadTexture("pigfarm", "assets/buildings/pigfarm.png");

    //Enemies
    TextureManager::LoadTexture("regular", "assets/player/idle.png");

    GameManager* game = GameManager::GetInstance();

    game->Run();
}
