#include <game_manager.h>

int main()
{
	GameManager* gameManager = GameManager::getInstance();
	
    // Game loop
    while (gameManager->isRunning()){
        gameManager->update();
        gameManager->render();
    }

    delete gameManager;

}