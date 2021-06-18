#pragma once

#include "game_object.h"

#include <glm/vec3.hpp>

class Stick: public GameObject
{
    public:
        glm::vec3 direction;
        float power;
        Stick(glm::vec3 dir, float pow);
        Stick();

};