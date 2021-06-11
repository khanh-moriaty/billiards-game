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
    Texture texture0("res/texture/wall.jpg", GL_TEXTURE_2D, 0);
    Texture texture1("res/texture/floor.png", GL_TEXTURE_2D, 1);
    Texture texture2("res/texture/door.jpg", GL_TEXTURE_2D, 2);
    Texture texture3("res/texture/pic.jpg", GL_TEXTURE_2D, 3);
    Texture texture4("res/texture/green.jpg", GL_TEXTURE_2D, 4);
    Texture texture5("res/texture/body_wood.jpg", GL_TEXTURE_2D, 5);
    Texture texture6("res/texture/leg.jpg", GL_TEXTURE_2D, 6);
    Texture texture7("res/texture/light.jpg", GL_TEXTURE_2D, 7);
    Texture texture8("res/texture/white.jpg", GL_TEXTURE_2D, 8);
    
    Texture textureBall0("res/texture/ball0.jpg", GL_TEXTURE_2D, 9);
    Texture textureBall1("res/texture/ball1.jpg", GL_TEXTURE_2D, 9);
    Texture textureBall2("res/texture/ball2.jpg", GL_TEXTURE_2D, 9);
    Texture textureBall3("res/texture/ball3.jpg", GL_TEXTURE_2D, 9);
    Texture textureBall4("res/texture/ball4.jpg", GL_TEXTURE_2D, 9);
    Texture textureBall5("res/texture/ball5.jpg", GL_TEXTURE_2D, 9);
    Texture textureBall6("res/texture/ball6.jpg", GL_TEXTURE_2D, 9);
    Texture textureBall7("res/texture/ball7.jpg", GL_TEXTURE_2D, 9);
    Texture textureBall8("res/texture/ball8.jpg", GL_TEXTURE_2D, 9);
    Texture textureBall9("res/texture/ball9.jpg", GL_TEXTURE_2D, 9);
    Texture textureBall10("res/texture/ball10.jpg", GL_TEXTURE_2D, 9);
    Texture textureBall11("res/texture/ball11.jpg", GL_TEXTURE_2D, 9);
    Texture textureBall12("res/texture/ball12.jpg", GL_TEXTURE_2D, 9);
    Texture textureBall13("res/texture/ball13.jpg", GL_TEXTURE_2D, 9);
    Texture textureBall14("res/texture/ball14.jpg", GL_TEXTURE_2D, 9);
    Texture textureBall15("res/texture/ball15.jpg", GL_TEXTURE_2D, 10);

    this->mesh.push_back(new Mesh(wall.data(), wall.size(), NULL, 0, texture0, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(floor.data(), floor.size(), NULL, 0, texture1, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(door.data(), door.size(), NULL, 0, texture2, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(pic.data(), pic.size(), NULL, 0, texture3, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(face.data(), face.size(), NULL, 0, texture4, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(body.data(), body.size(), NULL, 0,  texture5, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(leg.data(), leg.size(), NULL, 0, texture6, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(chair.data(), chair.size(), NULL, 0, texture7, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(chair.data(), chair.size(), NULL, 0, texture7, glm::vec3(6.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(lightB.data(), lightB.size(), NULL, 0, texture7, glm::vec3(0.f, 1.f, 0.8f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(lightW.data(), lightW.size(), NULL, 0, texture8, glm::vec3(0.f, 1.f, 0.8f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));

    Primitive* ball_primitive = new Sphere();

    this->mesh.push_back(new Mesh(ball_primitive, textureBall0, glm::vec3(0.f, 1.0f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureBall1, glm::vec3(0.f, 1.0f, 0.1f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureBall2, glm::vec3(0.f, 1.0f, 0.2f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureBall3, glm::vec3(0.f, 1.0f, 0.3f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureBall4, glm::vec3(0.1f, 1.0f, 0.0f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureBall5, glm::vec3(0.2f, 1.0f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureBall6, glm::vec3(0.3f, 1.0f, 0.0f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureBall7, glm::vec3(0.1f, 1.0f, 0.1f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureBall8, glm::vec3(0.2f, 1.0f, 0.2f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureBall9, glm::vec3(0.3f, 1.0f, 0.3f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureBall10, glm::vec3(0.2f, 1.0f, 0.3f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureBall11, glm::vec3(0.3f, 1.0f, 0.2f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureBall12, glm::vec3(0.1f, 1.0f, 0.2f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureBall13, glm::vec3(0.2f, 1.0f, 0.1f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureBall14, glm::vec3(0.1f, 1.0f, 0.3f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->mesh.push_back(new Mesh(ball_primitive, textureBall15, glm::vec3(0.3f, 1.0f, 0.1f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));

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
