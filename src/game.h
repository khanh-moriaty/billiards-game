#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shaders/shader.h"
#include "texture.h"
#include "vertex.h"
#include "primitives.h"
#include "mesh.h"
#include "camera.h"
#include "utils/loader.h"
#include "texture_manager.h"

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

    TextureManager textureManager;

    glm::mat4 ModelMatrix;
    glm::mat4 ViewMatrix; 
    glm::mat4 ProjectionMatrix;
    glm::vec3 lightPos0;

    float nearPlane = 0.1f;
    float farPlane = 1000.f;

    void init();
    void createObjects();
    void initMatrices();

    GameManager(const int SCR_WIDTH, const int SCR_HEIGHT);

public:

    static GameManager* getInstance();

    ~GameManager();

    bool isRunning();
    void update();
    void render();

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