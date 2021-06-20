#pragma once

#include <vector>

#include "game_objects/game_object.h"
#include <texture/texture_manager.h>

struct Light {
    Mesh *cover;
    Mesh *string;
    Mesh *bulb;
    glm::vec3 position;
};

class ObjectManager
{
private:
    static const float ROOM_HEIGHT;

    TextureManager* textureManager;
    std::vector<GameObject *> objectList;
    Light lights[3];

public:
    ObjectManager(TextureManager* textureManager);

    ~ObjectManager()
    {
        for (auto x : this->objectList)
            delete x;

        for (auto x : this->lights){
            delete x.bulb;
            delete x.cover;
            delete x.string;
        }
    }

    void initRoom();
    void addBall(int number, glm::vec3 position = glm::vec3(0.f));
    void addLight(int i, glm::vec3 position = glm::vec3(0.f));

    void update();
    void render(Shader* shader);

    const glm::vec3 getLight0() {return lights[0].position;}
    const glm::vec3 getLight1() {return lights[1].position;}
    const glm::vec3 getLight2() {return lights[2].position;}
};