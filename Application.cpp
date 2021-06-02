#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <iostream>
#include <string>
#include <fstream>
#include <SOIL2.h>
#include "Shader.h"
#include "Texture.h"
#include <sstream>
#include "Vertex.h"
#include "Primitives.h"
#include "Mesh.h"
#include "Camera.h"
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
static std::vector<Vertex> loadOBJ(const char* file_name)
{
    //Vertex portions
    std::vector<glm::fvec3> vertex_positions;
    std::vector<glm::fvec2> vertex_texcoords;
    std::vector<glm::fvec3> vertex_normals;

    //Face vectors
    std::vector<GLint> vertex_position_indicies;
    std::vector<GLint> vertex_texcoord_indicies;
    std::vector<GLint> vertex_normal_indicies;

    //Vertex array
    std::vector<Vertex> vertices;

    std::stringstream ss;
    std::ifstream in_file(file_name);
    std::string line = "";
    std::string prefix = "";
    glm::vec3 temp_vec3;
    glm::vec2 temp_vec2;
    GLint temp_glint = 0;

    //File open error check
    if (!in_file.is_open())
    {
        throw "ERROR::OBJLOADER::Could not open file.";
    }

    //Read one line at a time
    while (std::getline(in_file, line))
    {
        //Get the prefix of the line
        ss.clear();
        ss.str(line);
        ss >> prefix;

        if (prefix == "#")
        {

        }
        else if (prefix == "o")
        {

        }
        else if (prefix == "s")
        {

        }
        else if (prefix == "use_mtl")
        {

        }
        else if (prefix == "v") //Vertex position
        {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            vertex_positions.push_back(temp_vec3);
        }
        else if (prefix == "vt")
        {
            ss >> temp_vec2.x >> temp_vec2.y;
            vertex_texcoords.push_back(temp_vec2);
        }
        else if (prefix == "vn")
        {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            vertex_normals.push_back(temp_vec3);
        }
        else if (prefix == "f")
        {
            int counter = 0;
            while (ss >> temp_glint)
            {
                //Pushing indices into correct arrays
                if (counter == 0)
                    vertex_position_indicies.push_back(temp_glint);
                else if (counter == 1)
                    vertex_texcoord_indicies.push_back(temp_glint);
                else if (counter == 2)
                    vertex_normal_indicies.push_back(temp_glint);

                //Handling characters
                if (ss.peek() == '/')
                {
                    ++counter;
                    ss.ignore(1, '/');
                }
                else if (ss.peek() == ' ')
                {
                    ++counter;
                    ss.ignore(1, ' ');
                }

                //Reset the counter
                if (counter > 2)
                    counter = 0;
            }
        }
        else
        {

        }
    }

    //Build final vertex array (mesh)
    vertices.resize(vertex_position_indicies.size(), Vertex());

    //Load in all indices
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        vertices[i].position = vertex_positions[vertex_position_indicies[i] - 1];
        vertices[i].texcoord = vertex_texcoords[vertex_texcoord_indicies[i] - 1];
        vertices[i].normal = vertex_normals[vertex_normal_indicies[i] - 1];
        vertices[i].color = glm::vec3(1.f, 1.f, 1.f);
    }

    //DEBUG
    std::cout << "Nr of vertices: " << vertices.size() << "\n";

    //Loaded success
    std::cout << "OBJ file loaded!" << "\n";
    return vertices;
}

//create camera at position
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f)); 
float yaw = -90.0f;
float pitch = 0.0f;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
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
    Shader ourShader("vertex_core.glsl", "fragment_core.glsl");
    
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    //Quad temp = Quad();
    //Mesh test(&temp, glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f));
    
    //create set of objs
    std::vector<Mesh*>mesh;
    //create obj
    std::vector<Vertex> obj1;
    obj1 = loadOBJ("blender_files/combine2.obj");

    mesh.push_back(new Mesh(obj1.data(), obj1.size(), NULL, 0, glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f)));

    // load and create a texture 
    // -------------------------
    Texture texture0("pusheen.png", GL_TEXTURE_2D, 0);
    Texture texture1("container1.png", GL_TEXTURE_2D, 1);
   
    //init matrix
    glm::mat4 ModelMatrix(1.f);
    glm::mat4 ViewMatrix(1.f);
    ViewMatrix = camera.GetViewMatrix();

    float fov = 90.f;
    float nearPlane = 0.1f;
    float farPlane = 1000.f;
    glm::mat4 ProjectionMatrix(1.f);
    glm::vec3 lightPos0(0.f, 0.f, 1.f);
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
        glClearColor(0.0f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |GL_STENCIL_BUFFER_BIT);

        ourShader.use_Program();
        ourShader.set_1i(texture0.getunit(), "texture0");
        ourShader.set_1i(texture1.getunit(), "texture1");

        // bind Texture
        texture0.bind();
        texture1.bind();

        ourShader.set_Mat4fv(ModelMatrix, "ModelMatrix");
        glfwGetFramebufferSize(window, &w_buffer, &h_buffer);
        ProjectionMatrix = glm::perspective(glm::radians(camera.Zoom), static_cast<float> (w_buffer) / h_buffer, nearPlane, farPlane);
        ourShader.set_Mat4fv(ProjectionMatrix, "ProjectionMatrix");
        ViewMatrix = camera.GetViewMatrix();
        ourShader.set_Mat4fv(ViewMatrix, "ViewMatrix");

        for (auto& i : mesh)
        {
            i->render(&ourShader);            
        }
        
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
