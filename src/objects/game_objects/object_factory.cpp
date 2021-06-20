#include "object_factory.h"

#include "ball.h"
#include "light.h"

const float ObjectFactory::ROOM_HEIGHT = 6.f;
const float ObjectFactory::LIGHT_RADIUS = 0.2f;
const float ObjectFactory::LIGHT_HEIGHT = 0.15f;

ObjectFactory::ObjectFactory(TextureManager *textureManager){
    this->textureManager = textureManager;
}

GameObject* ObjectFactory::createBall(int number, glm::vec3 position)
{
    Primitive *ball = new Sphere(Ball::RADIUS);
    std::string textureName = "ball" + std::to_string(number);
    Texture *texture = this->textureManager->get(textureName);
    Mesh *mesh = new Mesh(ball, texture, position);
    mesh->setShininess(30.0f);
    delete ball;

    GameObject* obj = new Ball(number, mesh);
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