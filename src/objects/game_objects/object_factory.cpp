#include "object_factory.h"

#include "ball.h"
#include "light.h"

const float ObjectFactory::PI = 3.14f;

const float ObjectFactory::ROOM_WIDTH = 10.f;
const float ObjectFactory::ROOM_HEIGHT = 6.f;

const float ObjectFactory::WALL_DEPTH = 0.1f;
const float ObjectFactory::DOOR_WIDTH = 2.f;
const float ObjectFactory::DOOR_HEIGHT = 4.f;
const float ObjectFactory::PIC_WIDTH = 2.f;
const float ObjectFactory::PIC_HEIGHT = 2.f;

const float ObjectFactory::LIGHT_RADIUS = 0.2f;
const float ObjectFactory::LIGHT_HEIGHT = 0.15f;

ObjectFactory::ObjectFactory(TextureManager *textureManager){
    this->textureManager = textureManager;
}

GameObject* ObjectFactory::createBall(int number, glm::vec3 position, glm::vec3 direction, float power)
{
    Primitive *ball = new Sphere(Ball::RADIUS);
    std::string textureName = "ball" + std::to_string(number);
    Texture *texture = this->textureManager->get(textureName);
    Mesh *mesh = new Mesh(ball, texture, position);
    mesh->setShininess(30.0f);
    delete ball;

    GameObject* obj = new Ball(number, mesh, direction, power);
    return obj;
}

GameObject* ObjectFactory::createLight(glm::vec3 position){
    Primitive *primitive;
    Texture *texture;
    Mesh *meshCover, *meshString, *meshBulb;
    glm::vec3 meshPosition;

    const float LIGHT_RADIUS = 0.2f;
    const float LIGHT_HEIGHT = 0.15f;

    // All three components have the same origin (which is at the ceiling)
    glm::vec3 meshOrigin = glm::vec3(position.x, ROOM_HEIGHT, position.z);

    // Create light cover
    primitive = new Cone(LIGHT_RADIUS, LIGHT_HEIGHT);
    texture = textureManager->get("light");
    meshPosition = position;
    meshCover = new Mesh(primitive, texture, meshPosition, meshOrigin);
    delete primitive;

    // Create string
    primitive = new Cylinder(0.02f * LIGHT_RADIUS, ROOM_HEIGHT - (position.y + LIGHT_HEIGHT));
    texture = textureManager->get("light");
    meshPosition = glm::vec3(position.x, position.y + LIGHT_HEIGHT, position.z);
    meshString = new Mesh(primitive, texture, meshPosition, meshOrigin);
    delete primitive;

    // Create light bulb
    primitive = new Sphere(0.25f * LIGHT_RADIUS);
    texture = textureManager->get("white");
    meshPosition = glm::vec3(position.x, position.y + 0.25f * LIGHT_HEIGHT, position.z);
    meshBulb = new Mesh(primitive, texture, meshPosition, meshOrigin);
    delete primitive;

    // Create light object from 3 components
    GameObject* light = new Light(meshCover, meshString, meshBulb);
    return light;
}

GameObject* ObjectFactory::createWallLeft(){
    Primitive *primitive = new Plane(ROOM_WIDTH, ROOM_HEIGHT, WALL_DEPTH);
    Texture *texture = this->textureManager->get("wall");
    Mesh *mesh = new Mesh(primitive, texture, glm::vec3(-ROOM_WIDTH/2, ROOM_HEIGHT/2, 0.f));
    mesh->rotate(glm::vec3(0.f, PI/2, 0.f));
    delete primitive;

    GameObject* obj = new GameObject(mesh);
    return obj;
}

GameObject* ObjectFactory::createWallRight(){
    Primitive *primitive = new Plane(ROOM_WIDTH, ROOM_HEIGHT, WALL_DEPTH);
    Texture *texture = this->textureManager->get("wall");
    Mesh *mesh = new Mesh(primitive, texture, glm::vec3(0.f, ROOM_HEIGHT/2, -ROOM_WIDTH/2));
    delete primitive;

    GameObject* obj = new GameObject(mesh);
    return obj;
}

GameObject* ObjectFactory::createFloor(){
    Primitive *primitive = new Plane(ROOM_WIDTH, ROOM_WIDTH, WALL_DEPTH);
    Texture *texture = this->textureManager->get("floor");
    Mesh *mesh = new Mesh(primitive, texture, glm::vec3(0.f, 0.f, 0.f));
    mesh->rotate(glm::vec3(0.f, 0.f, PI/2));
    delete primitive;

    GameObject* obj = new GameObject(mesh);
    return obj;
}

GameObject* ObjectFactory::createDoor(){
    Primitive *primitive = new Plane(DOOR_WIDTH, DOOR_HEIGHT, WALL_DEPTH/4);
    Texture *texture = this->textureManager->get("door");
    Mesh *mesh = new Mesh(primitive, texture, glm::vec3(-ROOM_WIDTH/2 + WALL_DEPTH/2, DOOR_HEIGHT/2, ROOM_WIDTH/4));
    mesh->rotate(glm::vec3(0.f, PI/2, 0.f));
    delete primitive;

    GameObject* obj = new GameObject(mesh);
    return obj;
}

GameObject* ObjectFactory::createPic(){
    Primitive *primitive = new Plane(PIC_WIDTH, PIC_HEIGHT, WALL_DEPTH);
    Texture *texture = this->textureManager->get("pic");
    Mesh *mesh = new Mesh(primitive, texture, glm::vec3(-ROOM_WIDTH/4, ROOM_HEIGHT*.6, -ROOM_WIDTH/2 + WALL_DEPTH/2));
    delete primitive;

    GameObject* obj = new GameObject(mesh);
    return obj;
}