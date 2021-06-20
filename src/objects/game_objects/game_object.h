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
    virtual void collide(GameObject* gameobj) {};
    virtual void update() {}
    glm::vec3 getPos(){return this->mesh->getPos();}
    void render(Shader* shader) {this->mesh->render(shader);}
    virtual bool inHole() {return false;}
    virtual bool isBall() {return false;}
    virtual bool isStick() {return false;}
};