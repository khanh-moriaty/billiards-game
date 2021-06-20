#pragma once

#include "game_object.h"
#include <texture/texture_manager.h>

class ObjectFactory
{
private:
    static const float PI;

    static const float ROOM_WIDTH;
    static const float ROOM_HEIGHT;
    static const float WALL_DEPTH;
    static const float DOOR_WIDTH;
    static const float DOOR_HEIGHT;
    static const float PIC_WIDTH;
    static const float PIC_HEIGHT;
    static const float LIGHT_RADIUS;
    static const float LIGHT_HEIGHT;

    TextureManager *textureManager;

public:
    ObjectFactory(TextureManager *textureManager);
    GameObject *createBall(int number, glm::vec3 position, glm::vec3 direction, float power);
    GameObject *createLight(glm::vec3 position);
    GameObject *createWallLeft();
    GameObject *createWallRight();
    GameObject *createFloor();
    GameObject *createDoor();
    GameObject *createPic();
};