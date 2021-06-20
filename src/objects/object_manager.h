#pragma once

#include <vector>

#include "game_objects/game_object.h"
#include "game_objects/object_factory.h"

class ObjectManager
{
private:
    static const float ROOM_HEIGHT;

    ObjectFactory* objectFactory;
    TextureManager* textureManager;

    std::vector<GameObject *> objectList;
    GameObject* lights[3];

public:
    ObjectManager(TextureManager* textureManager);

    ~ObjectManager()
    {
        delete objectFactory;
        for (auto x : this->objectList)
            delete x;
    }

    void initRoom();
    void addBall(int number, glm::vec3 position);
    void addLight(int i, glm::vec3 position);

    void update();
    void render(Shader* shader);

    const glm::vec3 getLight0() {return lights[0]->getPosition();}
    const glm::vec3 getLight1() {return lights[1]->getPosition();}
    const glm::vec3 getLight2() {return lights[2]->getPosition();}
};