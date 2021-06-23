#include "object_manager.h"
#include <texture/texture_manager.h>
#include "game_objects/stick.h"
#include "game_objects/ball.h"

#include <utils/loader.h>

ObjectManager::ObjectManager(TextureManager* textureManager)
{
    this->objectFactory = new ObjectFactory(textureManager);
    this->textureManager = textureManager;

    this->objectList.push_back(this->objectFactory->createWallLeft());
    this->objectList.push_back(this->objectFactory->createWallRight());
    this->objectList.push_back(this->objectFactory->createFloor());
    this->objectList.push_back(this->objectFactory->createDoor());
    this->objectList.push_back(this->objectFactory->createPic());
}

void ObjectManager::addBall(int number, glm::vec3 position, glm::vec3 direction, float power)
{
    this->objectList.push_back(objectFactory->createBall(number, position, direction, power));
}

void ObjectManager::addLight(int i, glm::vec3 position){
    GameObject* light = objectFactory->createLight(position);
    this->objectList.push_back(light);
    this->lights[i] = light;
}

void ObjectManager::addStick()
{
    //


    //
    this->objectList.push_back(new Stick());
}

void ObjectManager::removeBalls()
{
    std::vector<GameObject*>::iterator rm = std::end(this->objectList);
    for(std::vector<GameObject*>::iterator it = std::begin(this->objectList); it != std::end(this->objectList); ++it) {
        if ((*it)->isBall()) {
            rm = it;
            break;
        }
    }
    if (rm != std::end(this->objectList)) {
        this->objectList.erase(rm, std::end(this->objectList));
    }
}

GameObject* ObjectManager::getBall(int number){
    for(auto x: this->objectList){
        if (!x->isBall()) continue;
        if (((Ball*)x)->getNumber() == number) {
            return x;
        }
    }
    return NULL;
}

void ObjectManager::removeBall(int number){
    std::vector<GameObject*>::iterator rm = std::end(this->objectList);
    for(std::vector<GameObject*>::iterator it = std::begin(this->objectList); it != std::end(this->objectList); ++it) {
        if ((*it)->isBall() && ((Ball*)(*it))->getNumber() == number) {
            rm = it;
            break;
        }
    }
    if (rm != std::end(this->objectList)) {
        this->objectList.erase(rm);
    }
}

void ObjectManager::initRoom()
{
    std::vector<Vertex> wall, floor, door, pic, face, body, leg, chair, lightB, lightW, ball;
    // wall = loadOBJ("res/model/wall.obj");
    // floor = loadOBJ("res/model/floor.obj");
    // door = loadOBJ("res/model/door.obj");
    // pic = loadOBJ("res/model/pic.obj");
    face = loadOBJ("res/model/face.obj");
    body = loadOBJ("res/model/body.obj");
    leg = loadOBJ("res/model/leg.obj");
    chair = loadOBJ("res/model/chair.obj");
    // lightB = loadOBJ("res/model/lightB.obj");
    // lightW = loadOBJ("res/model/lightW.obj");

    Mesh *mesh;

    // mesh = new Mesh(wall, textureManager->get("wall"), glm::vec3(0.f, 0.f, 0.f));
    // this->objectList.push_back(new GameObject(mesh));

    // mesh = new Mesh(floor, textureManager->get("floor"), glm::vec3(0.f, 0.f, 0.f));
    // this->objectList.push_back(new GameObject(mesh));

    // mesh = new Mesh(door, textureManager->get("door"), glm::vec3(0.f, 0.f, 0.f));
    // this->objectList.push_back(new GameObject(mesh));

    // mesh = new Mesh(pic, textureManager->get("pic"), glm::vec3(0.f, 0.f, 0.f));
    // this->objectList.push_back(new GameObject(mesh));

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
    int n = objectList.size();
    for (int x = 0; x < n; x++){
        for(int y = x+1; y < n; y++){
            if (objectList[x]->isBall() && objectList[y]->isBall()) {
                objectList[x]->collide(objectList[y]);
            }
        }

        objectList[x]->update();
    }
}

void ObjectManager::render(Shader* shader) {
    for (auto x: this->objectList){
        if(!x->inHole())
            x->render(shader);
    }
}