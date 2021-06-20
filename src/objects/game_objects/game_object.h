#pragma once
#include <objects/mesh.h>
#include <vector>
#include <string>

class GameObject
{
protected:
    const std::string name;
    std::vector<Mesh*> mesh;
    float mass;

public:
    GameObject() {}

    GameObject(Mesh** mesh, int n, float mass = 1.f) {
        this->mesh = std::vector<Mesh*>(mesh, mesh+n);
        this->mass = mass;
    }

    GameObject(Mesh* mesh, float mass = 1.f) {
        this->mesh.push_back(mesh);
        this->mass = mass;
    }

    ~GameObject(){
        for (auto x: this->mesh){
            delete x;
        }
    }

    virtual void update() {}

    void render(Shader* shader){
        for (auto x: this->mesh){
            x->render(shader);
        }
    }

    // Get position of i-th mesh
    glm::vec3 getPosition(int i=0) {return this->mesh[i]->getPosition();}
    glm::vec3 getPos(){return this->mesh[0]->getPosition();}
    virtual bool inHole() {return false;}
    virtual bool isBall() {return false;}
    virtual bool isStick() {return false;}
    virtual void collide(GameObject* gameobj) {};
};