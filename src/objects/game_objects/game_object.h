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

    GameObject(Mesh** mesh, float mass = 1.f, int n=1) {
        this->mesh = std::vector<Mesh*>(mesh, mesh+n);
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
};