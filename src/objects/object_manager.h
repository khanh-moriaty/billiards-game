#pragma once

#include <vector>

#include "game_objects/game_object.h"
#include <texture/texture_manager.h>

class ObjectManager
{
private:
    TextureManager* textureManager;

public:
    std::vector<GameObject *> objectList;
    ObjectManager(TextureManager* textureManager);

    ~ObjectManager()
    {
        for (auto x : this->objectList)
            delete x;
    }

    void initRoom();
    void addBall(int number, glm::vec3 position = glm::vec3(0.f), glm::vec3 direction = glm::vec3(0.f), float power = 0.f);
    void removeBalls();
    void addStick();
    void update();
    void render(Shader* shader);
};