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

    init();

    this->textureManager = new TextureManager();
    this->textureManager->initTexture();

    this->objectManager = new ObjectManager(this->textureManager);
    this->objectManager->initRoom();
    for (int i = 0; i < 16; i++)
    {
        this->objectManager->addBall(i, glm::vec3(0.2f * (i/4), 1.f, 0.2f * (i%4)));
    }

    this->objectManager->addLight(0, glm::vec3(0.f, 3.f, 0.f));
    this->objectManager->addLight(1, glm::vec3(-.5f, 3.f, 0.f));
    this->objectManager->addLight(2, glm::vec3(+.5f, 3.f, 0.f));

    this->shader = new Shader("src/shaders/vertex_core.glsl", "src/shaders/fragment_core.glsl");
    this->shader->use_Program();
    initMatrices();
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
    this->window = glfwCreateWindow(this->SCR_WIDTH, this->SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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

    this->shader->set_Mat4fv(this->ModelMatrix, "ModelMatrix");
    this->shader->set_Mat4fv(this->ViewMatrix, "ViewMatrix");
    this->shader->set_Mat4fv(this->ProjectionMatrix, "ProjectionMatrix");
    this->shader->set_3fv(this->objectManager->getLight0(), "lightPos0");
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

void GameManager::processInput(GLFWwindow *window)
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

    gameManager->getCamera()->ProcessMouseMovement(xoffset, yoffset);
}

void GameManager::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    GameManager *gameManager = GameManager::getInstance();
    gameManager->getCamera()->ProcessMouseScroll(yoffset);
}
