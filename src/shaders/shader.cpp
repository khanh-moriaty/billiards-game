#include "shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Shader::Shader(const char* vertex_file, const char* fragment_file, const char* geometry_file)
{
    unsigned int vertexShader = 0;
    unsigned int fragmentShader = 0; 
    unsigned int geometryShader = 0;

    vertexShader = this->load_Shader(GL_VERTEX_SHADER, vertex_file);
    fragmentShader = this->load_Shader(GL_FRAGMENT_SHADER, fragment_file);
    if (geometry_file != nullptr)
        geometryShader = this->load_Shader(GL_GEOMETRY_SHADER, geometry_file);

    this->link_Program(vertexShader, fragmentShader, geometryShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if (geometry_file != nullptr)
        glDeleteShader(geometryShader);
}

Shader::~Shader()
{
    glDeleteProgram(this->id);
}


GLuint Shader::load_Shader(GLenum type,const char* filename)
{
    //read file
    std::ifstream input_file(filename);
    std::string src;
    std::string temp;

    while (std::getline(input_file, temp))
    {
        src += temp + "\n";
    }
    input_file.close();


    GLint success;
    char infoLog[512];
    GLuint shader;
    const char* Src = src.c_str();
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &Src, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);   //check compile fail or success
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR cant load source\n" << filename << std::endl << infoLog << std::endl;
    }
    src = "";
    temp = "";
    return shader;
}

void Shader::link_Program(unsigned int vertexShader, unsigned int fragmentShader, unsigned int geometryShader)
{
    char infoLog[512];
    GLint success;

    this->id = glCreateProgram();

    glAttachShader(this->id, vertexShader);
    if (geometryShader != 0)
        glAttachShader(this->id, geometryShader);
    glAttachShader(this->id, fragmentShader);
    glLinkProgram(this->id);

    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->id, 512, NULL, infoLog);
        std::cout << "ERROR cant link program" << infoLog << "\n";
    }
    glUseProgram(0);
}

void Shader::use_Program()
{
    glUseProgram(this->id);
}

void Shader::unuse_Program()
{
    glUseProgram(0);
}

//set uniform function
void Shader::set_1i(GLint value, const GLchar* name)
{
    this->use_Program();

    glUniform1i(glGetUniformLocation(this->id, name), value);

    this->unuse_Program();
}

void Shader::set_1f(GLfloat value, const GLchar* name)
{
    this->use_Program();

    glUniform1f(glGetUniformLocation(this->id, name), value);

    this->unuse_Program();
}

void Shader::set_2fv(glm::fvec2 value, const GLchar* name)
{
    this->use_Program();

    glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

    this->unuse_Program();
}

void Shader::set_3fv(glm::fvec3 value, const GLchar* name)
{
    this->use_Program();

    glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

    this->unuse_Program();
}

void Shader::set_4fv(glm::fvec4 value, const GLchar* name)
{
    this->use_Program();

    glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

    this->unuse_Program();
}

void Shader::set_Mat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose)
{
    this->use_Program();

    glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

    this->unuse_Program();
}

void Shader::set_Mat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose)
{
    this->use_Program();

    glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

    this->unuse_Program();
}