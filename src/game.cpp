#pragma once
#include <game.h>
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
    this->shader = new Shader("src/shaders/vertex_core.glsl", "src/shaders/fragment_core.glsl");
    this->shader->use_Program();

    initMatrices();
    createObjects();
}

GameManager::~GameManager()
{
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();

    delete this->camera;
    delete this->shader;
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
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//ko hien thi con tro chuot
    glfwSetCursorPosCallback(this->window, mouse_callback);
    glfwSetScrollCallback(this->window, scroll_callback);
    glfwMakeContextCurrent(this->window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        printf("Error\n");
        this->running = false;
        return;
    }
    glEnable(GL_DEPTH_TEST);
}

void GameManager::createObjects()
{
    //create set of objs
    
    //create obj
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

    // load and create a texture 
    // -------------------------

    textureManager.addTexture2D("wall", "res/texture/wall.jpg");
    textureManager.addTexture2D("floor", "res/texture/floor.png");
    textureManager.addTexture2D("door", "res/texture/door.jpg");
    textureManager.addTexture2D("pic", "res/texture/pic.jpg");
    textureManager.addTexture2D("green", "res/texture/green.jpg");
    textureManager.addTexture2D("body_wood", "res/texture/body_wood.jpg");
    textureManager.addTexture2D("leg", "res/texture/leg.jpg");
    textureManager.addTexture2D("light", "res/texture/light.jpg");
    textureManager.addTexture2D("white", "res/texture/white.jpg");

    textureManager.addTexture2D("ball0", "res/texture/ball0.jpg");
    textureManager.addTexture2D("ball1", "res/texture/ball1.jpg");
    textureManager.addTexture2D("ball2", "res/texture/ball2.jpg");
    textureManager.addTexture2D("ball3", "res/texture/ball3.jpg");
    textureManager.addTexture2D("ball4", "res/texture/ball4.jpg");
    textureManager.addTexture2D("ball5", "res/texture/ball5.jpg");
    textureManager.addTexture2D("ball6", "res/texture/ball6.jpg");
    textureManager.addTexture2D("ball7", "res/texture/ball7.jpg");
    textureManager.addTexture2D("ball8", "res/texture/ball8.jpg");
    textureManager.addTexture2D("ball9", "res/texture/ball9.jpg");
    textureManager.addTexture2D("ball10", "res/texture/ball10.jpg");
    textureManager.addTexture2D("ball11", "res/texture/ball11.jpg");
    textureManager.addTexture2D("ball12", "res/texture/ball12.jpg");
    textureManager.addTexture2D("ball13", "res/texture/ball13.jpg");
    textureManager.addTexture2D("ball14", "res/texture/ball14.jpg");
    textureManager.addTexture2D("ball15", "res/texture/ball15.jpg");

    this->mesh.push_back(new Mesh(wall.data(), wall.size(), NULL, 0, textureManager.get("wall"), glm::vec3(0.f, 0.f, 0.f)));
    this->mesh.push_back(new Mesh(floor.data(), floor.size(), NULL, 0, textureManager.get("floor"), glm::vec3(0.f, 0.f, 0.f)));
    this->mesh.push_back(new Mesh(door.data(), door.size(), NULL, 0, textureManager.get("door"), glm::vec3(0.f, 0.f, 0.f)));
    this->mesh.push_back(new Mesh(pic.data(), pic.size(), NULL, 0, textureManager.get("pic"), glm::vec3(0.f, 0.f, 0.f)));
    this->mesh.push_back(new Mesh(face.data(), face.size(), NULL, 0, textureManager.get("green"), glm::vec3(0.f, 0.f, 0.f)));
    this->mesh.push_back(new Mesh(body.data(), body.size(), NULL, 0,  textureManager.get("body_wood"), glm::vec3(0.f, 0.f, 0.f)));
    this->mesh.push_back(new Mesh(leg.data(), leg.size(), NULL, 0, textureManager.get("leg"), glm::vec3(0.f, 0.f, 0.f)));
    this->mesh.push_back(new Mesh(chair.data(), chair.size(), NULL, 0, textureManager.get("body_wood"), glm::vec3(0.f, 0.f, 0.f)));
    this->mesh.push_back(new Mesh(chair.data(), chair.size(), NULL, 0, textureManager.get("body_wood"), glm::vec3(6.f, 0.f, 0.f)));
    this->mesh.push_back(new Mesh(lightB.data(), lightB.size(), NULL, 0, textureManager.get("light"), glm::vec3(0.f, 1.f, 0.8f)));
    this->mesh.push_back(new Mesh(lightW.data(), lightW.size(), NULL, 0, textureManager.get("white"), glm::vec3(0.f, 1.f, 0.8f)));

    Primitive* ball_primitive = new Sphere();

    this->mesh.push_back(new Mesh(ball_primitive, textureManager.get("ball0"), glm::vec3(0.f, 1.0f, 0.f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureManager.get("ball1"), glm::vec3(0.f, 1.0f, 0.1f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureManager.get("ball2"), glm::vec3(0.f, 1.0f, 0.2f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureManager.get("ball3"), glm::vec3(0.f, 1.0f, 0.3f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureManager.get("ball4"), glm::vec3(0.1f, 1.0f, 0.0f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureManager.get("ball5"), glm::vec3(0.2f, 1.0f, 0.f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureManager.get("ball6"), glm::vec3(0.3f, 1.0f, 0.0f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureManager.get("ball7"), glm::vec3(0.1f, 1.0f, 0.1f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureManager.get("ball8"), glm::vec3(0.2f, 1.0f, 0.2f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureManager.get("ball9"), glm::vec3(0.3f, 1.0f, 0.3f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureManager.get("ball10"), glm::vec3(0.2f, 1.0f, 0.3f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureManager.get("ball11"), glm::vec3(0.3f, 1.0f, 0.2f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureManager.get("ball12"), glm::vec3(0.1f, 1.0f, 0.2f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureManager.get("ball13"), glm::vec3(0.2f, 1.0f, 0.1f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureManager.get("ball14"), glm::vec3(0.1f, 1.0f, 0.3f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureManager.get("ball15"), glm::vec3(0.3f, 1.0f, 0.1f)));

    delete ball_primitive;
}

void GameManager::initMatrices()
{
    //init matrix
    this->ModelMatrix = glm::mat4(1.f);
    this->ViewMatrix = this->camera->GetViewMatrix();

    float fov = 90.f;
    this->ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float> (w_buffer)/ h_buffer, nearPlane, farPlane);
    
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
    
    // render
    // ------
    glClearColor(0.f, 0.f, 0.f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |GL_STENCIL_BUFFER_BIT);

    this->shader->set_Mat4fv(this->ModelMatrix, "ModelMatrix");
    glfwGetFramebufferSize(this->window, &w_buffer, &h_buffer);
    this->ProjectionMatrix = glm::perspective(glm::radians(this->camera->Zoom), static_cast<float> (w_buffer) / h_buffer, nearPlane, farPlane);
    this->shader->set_Mat4fv(this->ProjectionMatrix, "ProjectionMatrix");
    this->ViewMatrix = this->camera->GetViewMatrix();
    this->shader->set_Mat4fv(this->ViewMatrix, "ViewMatrix");
}

void GameManager::render()
{
    for (auto& i : this->mesh)
    {
        // bind Texture
        i->render(this->shader);            
    }
    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

void GameManager::processInput(GLFWwindow* window)
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

    if (gameManager->lastX == -1){
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
