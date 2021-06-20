#include "light.h"

Light::Light(Mesh* meshCover, Mesh* meshString, Mesh* meshBulb) {
    this->mesh.push_back(meshCover);
    this->mesh.push_back(meshString);
    this->mesh.push_back(meshBulb);
    this->mass = 1.f;
}

void Light::update(){}