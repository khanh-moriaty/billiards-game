#pragma once

#include <vector>

#include "game_objects/game_object.h"
#include <texture/texture_manager.h>

class ObjectManager
{
private:
    TextureManager* textureManager;
    std::vector<GameObject *> objectList;

public:
    ObjectManager(TextureManager* textureManager);

    ~ObjectManager()
    {
        for (auto x : this->objectList)
            delete x;
    }

    void initRoom();
    void addBall(int number, glm::vec3 position = glm::vec3(0.f));
    void addLight(glm::vec3 position = glm::vec3(0.f));

    void update();
    void render(Shader* shader);
};