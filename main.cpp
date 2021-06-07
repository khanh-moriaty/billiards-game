#include "shaders/shader.h"
#include "texture.h"
#include "vertex.h"
#include "primitives.h"
#include "mesh.h"
#include "camera.h"
#include "utils/loader.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//create camera at position
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f)); 
float yaw = -90.0f;
float pitch = 0.0f;
const unsigned int SCR_WIDTH = 1500;
const unsigned int SCR_HEIGHT = 844;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float deltaTime = 0.1f;	// time between current frame and last frame
float lastFrame = 0.0f;

// settings
int w_buffer = 0;
int h_buffer = 0;

int main()
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwGetFramebufferSize(window, &w_buffer, &h_buffer);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//ko hien thi con tro chuot
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        printf("Error\n");
    glEnable(GL_DEPTH_TEST);
    
    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("src/shaders/vertex_core.glsl", "src/shaders/fragment_core.glsl");
    
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    //Quad temp = Quad();
    //Mesh test(&temp, glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f));
    
    //create set of objs
    std::vector<Mesh*>mesh;
    //create obj
    std::vector<Vertex> wall, floor, door, pic, face, body, leg, chair, lightB, lightW;
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

    Sphere ball2 = Sphere();
    Sphere ball10 = Sphere();

    // load and create a texture 
    // -------------------------
    Texture texture0("res/texture/wall.jpg", GL_TEXTURE_2D, 0);
    Texture texture1("res/texture/floor.png", GL_TEXTURE_2D, 1);
    Texture texture2("res/texture/door.jpg", GL_TEXTURE_2D, 2);
    Texture texture3("res/texture/pic.jpg", GL_TEXTURE_2D, 3);
    // Texture texture4("res/texture/face.jpg", GL_TEXTURE_2D, 4);
    // Texture texture5("res/texture/body.jpg", GL_TEXTURE_2D, 5);
    Texture texture4("res/texture/green.jpg", GL_TEXTURE_2D, 4);
    Texture texture5("res/texture/body_wood.jpg", GL_TEXTURE_2D, 5);
    Texture texture6("res/texture/leg.jpg", GL_TEXTURE_2D, 6);
    Texture texture7("res/texture/light.jpg", GL_TEXTURE_2D, 7);
    Texture texture8("res/texture/white.jpg", GL_TEXTURE_2D, 8);
    Texture textureBall2("res/texture/ball2.jpg", GL_TEXTURE_2D, 9);
    Texture textureBall10("res/texture/ball10.jpg", GL_TEXTURE_2D, 10);

    mesh.push_back(new Mesh(wall.data(), wall.size(), NULL, 0, &texture0, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    mesh.push_back(new Mesh(floor.data(), floor.size(), NULL, 0, &texture1, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    mesh.push_back(new Mesh(door.data(), door.size(), NULL, 0, &texture2, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    mesh.push_back(new Mesh(pic.data(), pic.size(), NULL, 0, &texture3, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    mesh.push_back(new Mesh(face.data(), face.size(), NULL, 0, &texture4, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    mesh.push_back(new Mesh(body.data(), body.size(), NULL, 0,  &texture5, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    mesh.push_back(new Mesh(leg.data(), leg.size(), NULL, 0, &texture6, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    mesh.push_back(new Mesh(chair.data(), chair.size(), NULL, 0, &texture7, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    mesh.push_back(new Mesh(chair.data(), chair.size(), NULL, 0, &texture7, glm::vec3(6.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    mesh.push_back(new Mesh(lightB.data(), lightB.size(), NULL, 0, &texture7, glm::vec3(0.f, 1.f, 0.8f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));
    mesh.push_back(new Mesh(lightW.data(), lightW.size(), NULL, 0, &texture8, glm::vec3(0.f, 1.f, 0.8f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));

    mesh.push_back(new Mesh(&ball2, &textureBall2, glm::vec3(0.f, 0.96f, 0.3f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.05f)));
    mesh.push_back(new Mesh(&ball10, &textureBall10, glm::vec3(0.f, 0.96f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.05f)));


    //init matrix
    glm::mat4 ModelMatrix(1.f);
    glm::mat4 ViewMatrix(1.f);
    ViewMatrix = camera.GetViewMatrix();

    float fov = 90.f;
    float nearPlane = 0.1f;
    float farPlane = 1000.f;
    glm::mat4 ProjectionMatrix(1.f);
    glm::vec3 lightPos0(0.f, 0.f, 0.f);
    ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float> (w_buffer)/ h_buffer, nearPlane, farPlane);
    ourShader.use_Program();
 
    ourShader.set_Mat4fv(ModelMatrix, "ModelMatrix");
    ourShader.set_Mat4fv(ViewMatrix, "ViewMatrix");
    ourShader.set_Mat4fv(ProjectionMatrix, "ProjectionMatrix");
    ourShader.set_3fv(lightPos0, "lightPos0");
    ourShader.set_3fv(camera.GetPos(), "camPosition");
    
    ourShader.unuse_Program();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        // -----
        processInput(window);
        
        // render
        // ------
        glClearColor(0.f, 0.f, 0.f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |GL_STENCIL_BUFFER_BIT);

        ourShader.use_Program();
        // ourShader.set_1i(texture1.getunit(), "_texture");
        ourShader.set_Mat4fv(ModelMatrix, "ModelMatrix");
        glfwGetFramebufferSize(window, &w_buffer, &h_buffer);
        ProjectionMatrix = glm::perspective(glm::radians(camera.Zoom), static_cast<float> (w_buffer) / h_buffer, nearPlane, farPlane);
        ourShader.set_Mat4fv(ProjectionMatrix, "ProjectionMatrix");
        ViewMatrix = camera.GetViewMatrix();
        ourShader.set_Mat4fv(ViewMatrix, "ViewMatrix");

        for (auto& i : mesh)
        {
            // bind Texture
            i->render(&ourShader);            
        }

        // ourShader.set_1i(texture0.getunit(), "_texture"); // wall
        // texture0.bind();
        // mesh[0]->render(&ourShader);
        // ourShader.set_1i(texture1.getunit(), "_texture"); // floor
        // texture1.bind();
        // mesh[1]->render(&ourShader);
        // ourShader.set_1i(texture2.getunit(), "_texture"); // door
        // texture2.bind();
        // mesh[2]->render(&ourShader);
        // ourShader.set_1i(texture3.getunit(), "_texture"); // pic
        // texture3.bind();
        // mesh[3]->render(&ourShader);
        // ourShader.set_1i(texture4.getunit(), "_texture"); // face
        // texture4.bind();
        // mesh[4]->render(&ourShader);
        // ourShader.set_1i(texture6.getunit(), "_texture"); // body
        // texture6.bind();
        // mesh[5]->render(&ourShader);
        // ourShader.set_1i(texture6.getunit(), "_texture"); // leg
        // texture6.bind();
        // mesh[6]->render(&ourShader);
        // ourShader.set_1i(texture7.getunit(), "_texture"); // chair 1
        // texture7.bind();
        // mesh[7]->render(&ourShader);
        // ourShader.set_1i(texture7.getunit(), "_texture"); // chair 2
        // texture7.bind();
        // mesh[8]->render(&ourShader);
        // ourShader.set_1i(texture7.getunit(), "_texture"); // light black
        // texture7.bind();
        // mesh[9]->render(&ourShader);
        // ourShader.set_1i(texture8.getunit(), "_texture"); // light white
        // texture8.bind();
        // mesh[10]->render(&ourShader);
        // ourShader.set_1i(textureBall2.getunit(), "_texture"); // ball2
        // textureBall2.bind();
        // mesh[11]->render(&ourShader);
        // ourShader.set_1i(textureBall10.getunit(), "_texture"); // ball10
        // textureBall10.bind();
        // mesh[12]->render(&ourShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
