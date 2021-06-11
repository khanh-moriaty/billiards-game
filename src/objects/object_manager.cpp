#include "object_manager.h"
#include "game_objects/ball.h"

#include <utils/loader.h>

ObjectManager::ObjectManager(GameManager* gameManager)
{
    this->gameManager = gameManager;
}

void ObjectManager::addBall(int number, glm::vec3 position)
{
    Primitive *ball = new Sphere(Ball::RADIUS);
    std::string textureName = "ball" + std::to_string(number);
    Texture *texture = gameManager->getTexture(textureName);
    Mesh *mesh = new Mesh(ball, texture, position);
    delete ball;

    this->objectList.push_back(new Ball(number, mesh));
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
    lightB = loadOBJ("res/model/lightB.obj");
    lightW = loadOBJ("res/model/lightW.obj");

    Mesh *mesh;

    mesh = new Mesh(wall, gameManager->getTexture("wall"), glm::vec3(0.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(floor, gameManager->getTexture("floor"), glm::vec3(0.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(door, gameManager->getTexture("door"), glm::vec3(0.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(pic, gameManager->getTexture("pic"), glm::vec3(0.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(face, gameManager->getTexture("green"), glm::vec3(0.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(body, gameManager->getTexture("body_wood"), glm::vec3(0.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(leg, gameManager->getTexture("leg"), glm::vec3(0.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(chair, gameManager->getTexture("body_wood"), glm::vec3(0.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(chair, gameManager->getTexture("body_wood"), glm::vec3(6.f, 0.f, 0.f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(lightB, gameManager->getTexture("light"), glm::vec3(0.f, 1.f, 0.8f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(lightW, gameManager->getTexture("white"), glm::vec3(0.f, 1.f, 0.8f));
    this->objectList.push_back(new GameObject(mesh));
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