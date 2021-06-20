#pragma once

#include "game_object.h"
#include <texture/texture_manager.h>

class ObjectFactory
{
private:
    static const float ROOM_HEIGHT;
    static const float LIGHT_RADIUS;
    static const float LIGHT_HEIGHT;

    TextureManager *textureManager;

public:
    ObjectFactory(TextureManager *textureManager);
    GameObject *createBall(int number, glm::vec3 position);
    GameObject *createLight(glm::vec3 position);
};