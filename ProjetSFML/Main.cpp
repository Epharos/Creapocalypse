#include "Common.hpp"
#include "GameManager.hpp"

int main()
{
    GameManager* game = GameManager::GetInstance();

    game->Run();
}
