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

    TextureManager::LoadTexture("shotgun", "assets/turrets/shotgun.png");
    TextureManager::LoadTexture("shotgun_spawning", "assets/turrets/shotgun_spawning.png");
    TextureManager::LoadTexture("shotgun_firing", "assets/turrets/shotgun_firing.png");

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
    TextureManager::LoadTexture("regularIdle", "assets/enemies/regular/idle.png");
    TextureManager::LoadTexture("regularMoving", "assets/enemies/regular/moving.png");
    TextureManager::LoadTexture("regularAttacking", "assets/enemies/regular/attack.png");
    TextureManager::LoadTexture("regularDying", "assets/enemies/regular/dying.png");

    //UI
    TextureManager::LoadTexture("turretScreen", "assets/ui/turretScreen.png");
    TextureManager::LoadTexture("turretTab", "assets/ui/TurretSelector.png");

    GameManager* game = GameManager::GetInstance();

    game->Run();
}
