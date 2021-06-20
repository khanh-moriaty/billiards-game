#pragma once
#include "game_manager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

GameManager *GameManager::gameManager = NULL;

GameManager *GameManager::getInstance()
{
    if (gameManager == NULL)
    {
        gameManager = new GameManager(800, 600);
    }
    return gameManager;
}

GameManager::GameManager(const int SCR_WIDTH, const int SCR_HEIGHT)
{
    this->SCR_WIDTH = SCR_WIDTH;
    this->SCR_HEIGHT = SCR_HEIGHT;
    this->lastX = -1;
    this->lastY = -1;
    this->camera = new Camera(glm::vec3(2.0f, 3.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), yaw, pitch);

    this->running = true;
    this->blockCam = 0;
    init();
    this->shader = new Shader("src/shaders/vertex_core.glsl", "src/shaders/fragment_core.glsl");
    this->shader->use_Program();
    initMatrices();

    this->textureManager = new TextureManager();
    this->textureManager->initTexture();

    this->objectManager = new ObjectManager(this->textureManager);
    this->objectManager->initRoom();
    // for (int i = 0; i < 16; i++)
    // {
    //     this->objectManager->addBall(i, glm::vec3(0.2f * (i/4), 1.f, 0.2f * (i%4)));
    // }
    //this->objectManager->addStick(glm::vec3(1.f, 0.f, 1.f), 0.3f);
    this->objectManager->addBall(14, glm::vec3(-1.f, 1.f, -0.5f));
    this->objectManager->addBall(8, glm::vec3(-.5f, 1.f, -0.25f));
    this->objectManager->addBall(0, glm::vec3(-1.5f, 1.f, -0.5f));

}
void GameManager::reset()
{
    this->objectManager->removeBalls();
    this->objectManager->addBall(14, glm::vec3(-1.f, 1.f, -0.5f));
    this->objectManager->addBall(8, glm::vec3(-.5f, 1.f, -0.25f));
    this->objectManager->addBall(0, glm::vec3(-1.5f, 1.f, -0.5f));
}
GameManager::~GameManager()
{
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();

    delete this->camera;
    delete this->shader;
    delete this->textureManager;
    delete this->objectManager;
}

void GameManager::init()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE);  

    // glfw window creation
    // --------------------
    this->window = glfwCreateWindow(this->SCR_WIDTH, this->SCR_HEIGHT, "The Best Billiard Game", NULL, NULL);
    if (this->window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        this->running = false;
        return;
    }

    glfwGetFramebufferSize(this->window, &this->w_buffer, &this->h_buffer);
    // glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //ko hien thi con tro chuot
    glfwSetCursorPosCallback(this->window, mouse_callback);
    glfwSetScrollCallback(this->window, scroll_callback);
    glfwMakeContextCurrent(this->window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        printf("Error\n");
        this->running = false;
        return;
    }
    glEnable(GL_DEPTH_TEST);
}

void GameManager::initMatrices()
{
    //init matrix
    this->ModelMatrix = glm::mat4(1.f);
    this->ViewMatrix = this->camera->GetViewMatrix();

    float fov = 90.f;
    this->ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(w_buffer) / h_buffer, nearPlane, farPlane);

    this->lightPos0 = glm::vec3(0.f, 8.f, 0.f);

    this->shader->set_Mat4fv(this->ModelMatrix, "ModelMatrix");
    this->shader->set_Mat4fv(this->ViewMatrix, "ViewMatrix");
    this->shader->set_Mat4fv(this->ProjectionMatrix, "ProjectionMatrix");
    this->shader->set_3fv(this->lightPos0, "lightPos0");
    this->shader->set_3fv(this->camera->GetPos(), "camPosition");
}

bool GameManager::isRunning()
{
    return this->running && !glfwWindowShouldClose(this->window);
}

void GameManager::update()
{
    float currentFrame = glfwGetTime();
    this->deltaTime = currentFrame - this->lastFrame;
    this->lastFrame = currentFrame;
    // input
    // -----

    this->processInput(this->window);
    this->objectManager->update();

    this->shader->set_Mat4fv(this->ModelMatrix, "ModelMatrix");
    glfwGetFramebufferSize(this->window, &w_buffer, &h_buffer);
    this->ProjectionMatrix = glm::perspective(glm::radians(this->camera->Zoom), static_cast<float>(w_buffer) / h_buffer, nearPlane, farPlane);
    this->shader->set_Mat4fv(this->ProjectionMatrix, "ProjectionMatrix");
    //if(this->blockCam == 0)
        this->ViewMatrix = this->camera->GetViewMatrix();
    this->shader->set_Mat4fv(this->ViewMatrix, "ViewMatrix");
}

void GameManager::render()
{
    // render
    // ------
    glClearColor(0.f, 0.f, 0.f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    this->objectManager->render(this->shader);

    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

void GameManager::processInput(GLFWwindow *window)//, glm::vec3* direction, float* power)
{   
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        this->camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        this->camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        this->camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        this->camera->ProcessKeyboard(RIGHT, deltaTime);
    //replay
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        this->reset();
    }
    //set camera pos at bida 0 pos
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        //this->camera->setPos(glm::vec3(-1.5f, 1.f, -0.5f), glm::vec3(0.f, 1.f, 0.f), 0.f, 0.f);
        if(this->blockCam == 0){
            float radius = 1.f;
            float camX   = sin(glfwGetTime()) * radius;
            float camZ   = cos(glfwGetTime()) * radius;
            float yaw = this->camera->Yaw;
            float pitch = this->camera->Pitch;
            glm::vec3 pos = this->objectManager->objectList.back()->getPos();
            glm::vec3 dir = glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)), 
                                        sin(glm::radians(pitch)),
                                        sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
            this->camera->setViewMat(glm::normalize(-dir)*radius + pos, this->camera->Yaw, this->camera->Pitch);
        }
        this->blockCam = 1;
    }
    //set the diretion of stick
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        glm::vec3 direction = glm::vec3(this->camera->Front.x, 0, this->camera->Front.z);
        float power = 0.1f;
        glm::vec3 pos = this->objectManager->objectList.back()->getPos();
        this->objectManager->objectList.pop_back();
        this->objectManager->addBall(0, pos, direction, power);
        this->blockCam = 0;

    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {
        //*direction = glm::vec3(this->camera->Front.x, 0, this->camera->Front.z);
        //*power = 0.05f;
        this->blockCam = 0;
    }
    
}

void GameManager::mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    GameManager *gameManager = GameManager::getInstance();

    if (gameManager->lastX == -1)
    {
        gameManager->setMouseXY(xpos, ypos);
    }

    float xoffset = xpos - gameManager->getLastX();
    float yoffset = gameManager->getLastY() - ypos; // reversed since y-coordinates go from bottom to top

    gameManager->setMouseXY(xpos, ypos);

    if(gameManager->blockCam==1){
        float radius = 1.f;
        float camX   = sin(glfwGetTime()) * radius;
        float camZ   = cos(glfwGetTime()) * radius;
        float yaw = gameManager->camera->Yaw + xoffset*0.1f;
        float pitch = gameManager->camera->Pitch;
        glm::vec3 pos = gameManager->objectManager->objectList.back()->getPos();
        glm::vec3 dir = glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)), 
                                    sin(glm::radians(pitch)),
                                    sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
        gameManager->camera->setViewMat(glm::normalize(-dir)*radius + pos, yaw, pitch);
    }
    else
        gameManager->getCamera()->ProcessMouseMovement(xoffset, yoffset);
}

void GameManager::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    GameManager *gameManager = GameManager::getInstance();
    gameManager->getCamera()->ProcessMouseScroll(yoffset);
}
