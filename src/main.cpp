#include <game_manager.h>

int main()
{
	GameManager* gameManager = GameManager::getInstance();
	
    // Game loop
    while (gameManager->isRunning()){
        gameManager->update();
        gameManager->render();
        _sleep(20);
    }

    delete gameManager;

}