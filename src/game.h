#pragma once
#include "shaders/shader.h"
#include "texture.h"
#include "vertex.h"
#include "primitives.h"
#include "mesh.h"
#include "camera.h"
#include "utils/loader.h"

class GameManager
{
private:

    // singleton
    static GameManager* gameManager;

    //game screen
    GLFWwindow* window;
    const unsigned int SCR_WIDTH;
    const unsigned int SCR_HEIGHT;
    int w_buffer;
    int h_buffer;

    //time delta
    float currentFrame;
    float deltaTime;
    float lastFrame;

    //mouse
    bool firstMouse;
    float lastX;
    float lastY;

    //camera
    Camera camera;
    glm::vec3 cameraPosition;
    glm::vec3 cameraUp;
    float yaw;
    float pitch;

    //matrices
    glm::mat4 ModelMatrix;
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;

    float fov;
    float nearPlane;
    float farPlane;

    //light
    glm::vec3 lightPos0;

    //
    Shader shaders;
    std::vector<Texture*> textures;
    std::vector<Mesh*> meshs;
    std::vector<std::vector<Vertex>> objs;
    void initWindow();
    void initGlew();
    void initOptions();
    void initMatrices();
    void initShaders();
    void initObjs();
    void initTextures();
    void initMeshs();
    void initLight();
    void initUniform();
    void updateUniform();

    //contructor and detructor
    GameManager(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT):
    SCR_WIDTH(SCR_WIDTH),
    SCR_HEIGHT(SCR_HEIGHT),
    //shaders("src/shaders/vertex_core.glsl", "src/shaders/fragment_core.glsl"),
    camera(glm::vec3(2.0f, 3.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), -135.0f, -30.0f)
    {
        this->window = nullptr;
        this->w_buffer = 0;
        this->h_buffer = 0;
        this->fov = 90.f;
        this->nearPlane = 0.1f;
        this->farPlane = 1000.f;
        this->currentFrame = 0.f;
        this->deltaTime = 0.1f;
        this->lastFrame = 0.f;
        this->cameraPosition = glm::vec3(2.0f, 3.0f, 2.0f);
        this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        this->yaw = -135.0f;
        this->pitch = -30.0f;
        this->firstMouse = true;
        this->lastX = this->SCR_WIDTH/2.0f;
        this->lastY = this->SCR_HEIGHT/2.0f;
        this->initWindow();
        this->initGlew();
        this->initOptions();
        this->initMatrices();
        this->initShaders();
        this->initObjs();
        this->initTextures();
        this->initMeshs();
        this->initLight();
        this->initUniform();
        this->shaders.unuse_Program();
    }

public:

    static GameManager* getInstance();

    ~GameManager();

    int getWindowShouldClose();

    void setWindowShouldClose();

    void updateDt();
    void updateMouseInput();
    void updateKeyboardInput();
    void updateInput();
    void update();
    void render();

    float getLastX() {return this->lastX;}
    float getLastY() {return this->lastY;}

    void setMouseXY(float lastX, float lastY){
        this->lastX = lastX;
        this->lastY = lastY;
    }

    bool isFirstMouse() {return this->firstMouse;}
    void setFirstMouse(bool firstMouse) {this->firstMouse = firstMouse;}

    Camera* getCamera() {return &this->camera;}


    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};