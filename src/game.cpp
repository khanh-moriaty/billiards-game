#pragma once
#include <game.h>

GameManager* GameManager::gameManager = NULL;

GameManager* GameManager::getInstance(){
    if (gameManager == NULL) {
        gameManager = new GameManager(800, 600);
    }
    return gameManager;
}

void GameManager::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    this->window = glfwCreateWindow(this->SCR_WIDTH, this->SCR_HEIGHT, "Billiards Game", NULL, NULL);
    if (this->window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwGetFramebufferSize(this->window, &this->w_buffer, &this->h_buffer);
    glfwMakeContextCurrent(this->window);
}

void GameManager::initGlew()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        printf("Error\n");
        glfwTerminate();
    }
}

void GameManager::initOptions()
{
    //ko hien thi con tro chuot
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, this->mouse_callback);
    glfwSetScrollCallback(window, this->scroll_callback);

    glEnable(GL_DEPTH_TEST);
}

void GameManager::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    GameManager* gameManager = GameManager::getInstance();
    if (gameManager->isFirstMouse())
    {
        gameManager->setMouseXY(xpos, ypos);
        gameManager->setFirstMouse(false);
    }

    float xoffset = xpos - gameManager->getLastX();
    float yoffset = gameManager->getLastY() - ypos; // reversed since y-coordinates go from bottom to top

    gameManager->setMouseXY(xpos, ypos);

    gameManager->getCamera()->ProcessMouseMovement(xoffset, yoffset);
}

void GameManager::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    GameManager* gameManager = GameManager::getInstance();
    gameManager->getCamera()->ProcessMouseScroll(yoffset);
}

void GameManager::initMatrices()
{
    this->ModelMatrix = glm::mat4(1.f);
    this->ViewMatrix = glm::mat4(1.f);
    this->ProjectionMatrix = glm::mat4(1.f);
    this->ProjectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->w_buffer) / this->h_buffer, this->nearPlane, this->farPlane);
}

void GameManager::initShaders()
{
    this->shaders = Shader("src/shaders/vertex_core.glsl", "src/shaders/fragment_core.glsl");
}

void GameManager::initObjs()
{
    this->objs.push_back(loadOBJ("res/model/wall.obj"));   //0
    this->objs.push_back(loadOBJ("res/model/floor.obj"));  //1
    this->objs.push_back(loadOBJ("res/model/door.obj"));   //2
    this->objs.push_back(loadOBJ("res/model/pic.obj"));    //3
    this->objs.push_back(loadOBJ("res/model/face.obj"));   //4
    this->objs.push_back(loadOBJ("res/model/body.obj"));   //5
    this->objs.push_back(loadOBJ("res/model/leg.obj"));    //6
    this->objs.push_back(loadOBJ("res/model/chair.obj"));  //7
    this->objs.push_back(loadOBJ("res/model/lightB.obj")); //8
    this->objs.push_back(loadOBJ("res/model/lightW.obj")); //9
}

void GameManager::initTextures()
{
    this->textures.push_back(new Texture("res/texture/wall.jpg", GL_TEXTURE_2D, 0));
    this->textures.push_back(new Texture("res/texture/floor.png", GL_TEXTURE_2D, 1));
    this->textures.push_back(new Texture("res/texture/door.jpg", GL_TEXTURE_2D, 2));
    this->textures.push_back(new Texture("res/texture/pic.jpg", GL_TEXTURE_2D, 3));
    this->textures.push_back(new Texture("res/texture/green.jpg", GL_TEXTURE_2D, 4));
    this->textures.push_back(new Texture("res/texture/body_wood.jpg", GL_TEXTURE_2D, 5));
    this->textures.push_back(new Texture("res/texture/leg.jpg", GL_TEXTURE_2D, 6));
    this->textures.push_back(new Texture("res/texture/light.jpg", GL_TEXTURE_2D, 7));
    this->textures.push_back(new Texture("res/texture/white.jpg", GL_TEXTURE_2D, 8));
    this->textures.push_back(new Texture("res/texture/ball0.jpg", GL_TEXTURE_2D, 9));
    this->textures.push_back(new Texture("res/texture/ball1.jpg", GL_TEXTURE_2D, 9));
    this->textures.push_back(new Texture("res/texture/ball2.jpg", GL_TEXTURE_2D, 9));
    this->textures.push_back(new Texture("res/texture/ball3.jpg", GL_TEXTURE_2D, 9));
    this->textures.push_back(new Texture("res/texture/ball4.jpg", GL_TEXTURE_2D, 9));
    this->textures.push_back(new Texture("res/texture/ball5.jpg", GL_TEXTURE_2D, 9));
    this->textures.push_back(new Texture("res/texture/ball6.jpg", GL_TEXTURE_2D, 9));
    this->textures.push_back(new Texture("res/texture/ball7.jpg", GL_TEXTURE_2D, 9));
    this->textures.push_back(new Texture("res/texture/ball8.jpg", GL_TEXTURE_2D, 9));
    this->textures.push_back(new Texture("res/texture/ball9.jpg", GL_TEXTURE_2D, 9));
    this->textures.push_back(new Texture("res/texture/ball10.jpg", GL_TEXTURE_2D, 9));
    this->textures.push_back(new Texture("res/texture/ball11.jpg", GL_TEXTURE_2D, 9));
    this->textures.push_back(new Texture("res/texture/ball12.jpg", GL_TEXTURE_2D, 9));
    this->textures.push_back(new Texture("res/texture/ball13.jpg", GL_TEXTURE_2D, 9));
    this->textures.push_back(new Texture("res/texture/ball14.jpg", GL_TEXTURE_2D, 9));
    this->textures.push_back(new Texture("res/texture/ball15.jpg", GL_TEXTURE_2D, 10));
}

void GameManager::initMeshs()
{
    this->meshs.push_back(new Mesh(this->objs[0].data(), this->objs[0].size(), NULL, 0, this->textures[0], glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(this->objs[1].data(), this->objs[1].size(), NULL, 0, this->textures[1], glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(this->objs[2].data(), this->objs[2].size(), NULL, 0, this->textures[2], glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(this->objs[3].data(), this->objs[3].size(), NULL, 0, this->textures[3], glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(this->objs[4].data(), this->objs[4].size(), NULL, 0, this->textures[4], glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(this->objs[5].data(), this->objs[5].size(), NULL, 0, this->textures[5], glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(this->objs[6].data(), this->objs[6].size(), NULL, 0, this->textures[6], glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(this->objs[7].data(), this->objs[7].size(), NULL, 0, this->textures[7], glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(this->objs[7].data(), this->objs[7].size(), NULL, 0, this->textures[7], glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(this->objs[8].data(), this->objs[8].size(), NULL, 0, this->textures[7], glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(this->objs[9].data(), this->objs[9].size(), NULL, 0, this->textures[8], glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    Primitive *ball_primitive = new Sphere();
    this->meshs.push_back(new Mesh(ball_primitive, this->textures[9], glm::vec3(0.f, 1.0f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(ball_primitive, this->textures[10], glm::vec3(0.f, 1.0f, 0.1f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(ball_primitive, this->textures[11], glm::vec3(0.f, 1.0f, 0.2f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(ball_primitive, this->textures[12], glm::vec3(0.f, 1.0f, 0.3f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(ball_primitive, this->textures[13], glm::vec3(0.1f, 1.0f, 0.0f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(ball_primitive, this->textures[14], glm::vec3(0.2f, 1.0f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(ball_primitive, this->textures[15], glm::vec3(0.3f, 1.0f, 0.0f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(ball_primitive, this->textures[16], glm::vec3(0.1f, 1.0f, 0.1f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(ball_primitive, this->textures[17], glm::vec3(0.2f, 1.0f, 0.2f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(ball_primitive, this->textures[18], glm::vec3(0.3f, 1.0f, 0.3f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(ball_primitive, this->textures[19], glm::vec3(0.2f, 1.0f, 0.3f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(ball_primitive, this->textures[20], glm::vec3(0.3f, 1.0f, 0.2f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(ball_primitive, this->textures[21], glm::vec3(0.1f, 1.0f, 0.2f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(ball_primitive, this->textures[22], glm::vec3(0.2f, 1.0f, 0.1f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(ball_primitive, this->textures[23], glm::vec3(0.1f, 1.0f, 0.3f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    this->meshs.push_back(new Mesh(ball_primitive, this->textures[24], glm::vec3(0.3f, 1.0f, 0.1f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    delete ball_primitive;
}

void GameManager::initLight()
{
    this->lightPos0 = glm::vec3(0.f, 0.f, 0.f);
}

void GameManager::initUniform()
{
    this->shaders.set_Mat4fv(this->ModelMatrix, "ModelMatrix");
    this->shaders.set_Mat4fv(this->ViewMatrix, "ViewMatrix");
    this->shaders.set_3fv(this->lightPos0, "lightPos0");
    this->shaders.set_Mat4fv(this->ProjectionMatrix, "ProjectionMatrix");
}

void GameManager::updateUniform()
{
    this->ViewMatrix = this->camera.GetViewMatrix();
    this->shaders.set_Mat4fv(this->ViewMatrix, "ViewMatrix");
    this->shaders.set_3fv(this->camera.GetPos(), "camPosition");
    this->shaders.set_3fv(this->lightPos0, "lightPos0");

    glfwGetFramebufferSize(this->window, &this->w_buffer, &this->h_buffer);
    this->ProjectionMatrix = glm::perspective(glm::radians(this->camera.Zoom), static_cast<float>(this->w_buffer) / this->h_buffer, this->nearPlane, this->farPlane);
    this->shaders.set_Mat4fv(this->ProjectionMatrix, "ProjectionMatrix");
}

//contructor and detructor
GameManager::~GameManager()
{
    glfwDestroyWindow(this->window);
    glfwTerminate();

    for (size_t i = 0; i < this->textures.size(); i++)
        delete this->textures[i];

    for (size_t i = 0; i < this->meshs.size(); i++)
        delete this->meshs[i];
}

int GameManager::getWindowShouldClose()
{
    return glfwWindowShouldClose(this->window);
}

void GameManager::setWindowShouldClose()
{
    glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

void GameManager::updateDt()
{
    this->currentFrame = static_cast<float>(glfwGetTime());
    this->deltaTime = this->currentFrame - this->lastFrame;
    this->lastFrame = this->currentFrame;
}

void GameManager::updateKeyboardInput()
{
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, true);

    if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
        this->camera.ProcessKeyboard(FORWARD, this->deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
        this->camera.ProcessKeyboard(BACKWARD, this->deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
        this->camera.ProcessKeyboard(LEFT, this->deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
        this->camera.ProcessKeyboard(RIGHT, this->deltaTime);
}

void GameManager::updateInput()
{
    glfwPollEvents();
    //this->updateMouseInput();
    this->updateKeyboardInput();
    //this->scroll_callback();
}

void GameManager::update()
{
    this->updateDt();
    this->updateInput();
    this->updateUniform();
}

void GameManager::render()
{
    glClearColor(1.f, 0.f, 0.f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    this->shaders.use_Program();
    // printf("2");
    for (auto &i : this->meshs)
    {
        i->render(&this->shaders);
    }
    glfwSwapBuffers(this->window);
    glfwPollEvents();
}
