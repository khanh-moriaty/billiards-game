#pragma once

#include "game_object.h"

class Light: public GameObject {
private:
public:
    Light(Mesh* cover, Mesh* string, Mesh* bulb);

    void update();
};