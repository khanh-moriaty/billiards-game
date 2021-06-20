#include "object_manager.h"
#include "game_objects/ball.h"

#include <utils/loader.h>

ObjectManager::ObjectManager(TextureManager* textureManager)
{
    this->textureManager = textureManager;
}

void ObjectManager::addBall(int number, glm::vec3 position)
{
    Primitive *ball = new Sphere(Ball::RADIUS);
    std::string textureName = "ball" + std::to_string(number);
    Texture *texture = textureManager->get(textureName);
    Mesh *mesh = new Mesh(ball, texture, position);
    mesh->setShininess(30.0f);
    delete ball;

    this->objectList.push_back(new Ball(number, mesh));
}

#include <iostream>
void ObjectManager::addLight(glm::vec3 position){
    Primitive *primitive;
    std::string textureName;
    Texture *texture;
    Mesh *mesh;
    glm::vec3 meshPosition;

    const float LIGHT_RADIUS = 0.2f;
    const float LIGHT_HEIGHT = 0.15f;

    // Create light
    primitive = new Cone(LIGHT_RADIUS, LIGHT_HEIGHT);
    textureName = "light";
    texture = textureManager->get(textureName);
    meshPosition = position;
    mesh = new Mesh(primitive, texture, meshPosition);
    std::cout << primitive->getNrOfIndices() << std::endl;
    this->objectList.push_back(new GameObject(mesh));

    // Create string
    primitive = new Cylinder(0.02f * LIGHT_RADIUS, 4.f - (position.y + LIGHT_HEIGHT));
    textureName = "light";
    texture = textureManager->get(textureName);
    meshPosition = glm::vec3(position.x, position.y + LIGHT_HEIGHT, position.z);
    mesh = new Mesh(primitive, texture, meshPosition);
    std::cout << primitive->getNrOfIndices() << std::endl;
    this->objectList.push_back(new GameObject(mesh));

    // Create light bulb
    primitive = new Sphere(0.25f * LIGHT_RADIUS);
    textureName = "white";
    texture = textureManager->get(textureName);
    meshPosition = glm::vec3(position.x, position.y + 0.25f * LIGHT_HEIGHT, position.z);
    mesh = new Mesh(primitive, texture, meshPosition);
    std::cout << primitive->getNrOfIndices() << std::endl;
    this->objectList.push_back(new GameObject(mesh));

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

    mesh = new Mesh(lightB, textureManager->get("light"), glm::vec3(0.f, 1.f, 0.8f));
    this->objectList.push_back(new GameObject(mesh));

    mesh = new Mesh(lightW, textureManager->get("white"), glm::vec3(0.f, 1.f, 0.8f));
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