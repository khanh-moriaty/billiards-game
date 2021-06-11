#pragma once

#include <vector>

#include "game_objects/game_object.h"
#include <game_manager.h>

class GameManager;

class ObjectManager
{
private:
    GameManager* gameManager;
    std::vector<GameObject *> objectList;

public:
    ObjectManager(GameManager* gameManager);

    ~ObjectManager()
    {
        for (auto x : this->objectList)
            delete x;
    }

    void initRoom();
    void addBall(int number, glm::vec3 position = glm::vec3(0.f));

    void update();
    void render(Shader* shader);
};