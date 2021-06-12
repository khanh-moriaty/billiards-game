#pragma once
#include <objects/mesh.h>

class GameObject
{
protected:
    Mesh* mesh;
    float mass;

public:
    GameObject() {}

    GameObject(Mesh* mesh, float mass = 1.f) {
        this->mesh = mesh;
        this->mass = mass;
    }

    ~GameObject() {delete mesh;}

    virtual void update() {}
    void render(Shader* shader) {this->mesh->render(shader);}
};