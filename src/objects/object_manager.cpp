#include "object_manager.h"
#include <texture/texture_manager.h>

#include <utils/loader.h>

ObjectManager::ObjectManager(TextureManager* textureManager)
{
    this->objectFactory = new ObjectFactory(textureManager);
    this->textureManager = textureManager;
}

void ObjectManager::addBall(int number, glm::vec3 position)
{
    this->objectList.push_back(objectFactory->createBall(number, position));
}

void ObjectManager::addLight(int i, glm::vec3 position){
    GameObject* light = objectFactory->createLight(position);
    this->objectList.push_back(light);
    this->lights[i] = light;
}

void ObjectManager::initRoom()
{
    std::vector<Vertex> wall, floor, door, pic, face, body, leg, chair, lightB, lightW, ball;
    wall = loadOBJ("res/model/wall.obj");
    floor = loadOBJ("res/model/floor.obj");
    door = loadOBJ("res/model/door.obj");
    pic = loadOBJ("res/model/pic.obj");
    face = loadOBJ("res/model/face.obj");
    body = loadOBJ("res/model/body.obj");
    leg = loadOBJ("res/model/leg.obj");
    chair = loadOBJ("res/model/chair.obj");
    // lightB = loadOBJ("res/model/lightB.obj");
    // lightW = loadOBJ("res/model/lightW.obj");

    Mesh *mesh;

    mesh = new Mesh(wall, textureManager->get("wall"), glm::vec3(0.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(floor, textureManager->get("floor"), glm::vec3(0.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(door, textureManager->get("door"), glm::vec3(0.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(pic, textureManager->get("pic"), glm::vec3(0.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(face, textureManager->get("green"), glm::vec3(0.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(body, textureManager->get("body_wood"), glm::vec3(0.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(leg, textureManager->get("leg"), glm::vec3(0.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(chair, textureManager->get("body_wood"), glm::vec3(0.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(chair, textureManager->get("body_wood"), glm::vec3(6.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    // mesh = new Mesh(lightB, textureManager->get("light"), glm::vec3(0.f, 1.f, 0.8f));
    // this->objectList.push_back(new GameObject(mesh));

    // mesh = new Mesh(lightW, textureManager->get("white"), glm::vec3(0.f, 1.f, 0.8f));
    // this->objectList.push_back(new GameObject(mesh));

}

void ObjectManager::update() {
    for (auto x: this->objectList){
        x->update();
    }
}

void ObjectManager::render(Shader* shader) {
    for (auto x: this->objectList){
        x->render(shader);
    }
}