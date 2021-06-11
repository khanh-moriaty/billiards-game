#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <shaders/shader.h>
#include <objects/vertex.h>
#include <objects/primitives/primitive.h>
#include <texture/texture.h>
#include <texture/texture_manager.h>
#include <objects/mesh.h>
#include <objects/object_manager.h>
#include <utils/loader.h>
#include <camera.h>

class ObjectManager;

class GameManager
{
private:

    // singleton
    static GameManager* gameManager;

    GLFWwindow* window;
    bool running = false;

    int SCR_WIDTH, SCR_HEIGHT;
    int w_buffer, h_buffer;

    //create camera at position
    float yaw = -135.0f; // Horizontal direction
    float pitch = -30.0f; // Vertical direction
    Camera* camera; 
    float lastX;
    float lastY;
    float deltaTime;	// time between current frame and last frame
    float lastFrame = 0.0f;

    Shader* shader;
    std::vector<Mesh*> mesh;

    ObjectManager* objectManager;
    TextureManager* textureManager;

    glm::mat4 ModelMatrix;
    glm::mat4 ViewMatrix; 
    glm::mat4 ProjectionMatrix;
    glm::vec3 lightPos0;

    float nearPlane = 0.1f;
    float farPlane = 1000.f;

    void init();
    void initMatrices();

    GameManager(const int SCR_WIDTH, const int SCR_HEIGHT);

public:

    static GameManager* getInstance();

    ~GameManager();

    bool isRunning();
    void update();
    void render();

    Texture* getTexture(std::string name) {return this->textureManager->operator[](name);}

    float getLastX() {return this->lastX;}
    float getLastY() {return this->lastY;}

    void setMouseXY(float lastX, float lastY){
        this->lastX = lastX;
        this->lastY = lastY;
    }

    Camera* getCamera() {return this->camera;}

    void processInput(GLFWwindow* window);

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};