#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp> 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader
{
private:
	GLuint id;
	GLuint load_Shader(GLenum type,const char* filename)
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
			std::cout << "ERROR cant load source\n" << filename << std::endl;
		}
		src = "";
		temp = "";
		return shader;
	}

	void link_Program(unsigned int vertexShader, unsigned int fragmentShader, unsigned int geometryShader)
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

public:
	Shader(const char* vertex_file, const char* fragment_file, const char* geometry_file = nullptr)
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

	~Shader()
	{
		glDeleteProgram(this->id);
	}
	GLint getid()
	{
		return this->id;
	}
	void use_Program()
	{
		glUseProgram(this->id);
	}

	void unuse_Program()
	{
		glUseProgram(0);
	}

	//set uniform function
	void set_1i(GLint value, const GLchar* name)
	{
		this->use_Program();

		glUniform1i(glGetUniformLocation(this->id, name), value);

		this->unuse_Program();
	}

	void set_1f(GLfloat value, const GLchar* name)
	{
		this->use_Program();

		glUniform1f(glGetUniformLocation(this->id, name), value);

		this->unuse_Program();
	}

	void set_2fv(glm::fvec2 value, const GLchar* name)
	{
		this->use_Program();

		glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuse_Program();
	}

	void set_3fv(glm::fvec3 value, const GLchar* name)
	{
		this->use_Program();

		glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuse_Program();
	}

	void set_4fv(glm::fvec4 value, const GLchar* name)
	{
		this->use_Program();

		glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuse_Program();
	}

	void set_Mat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{
		this->use_Program();

		glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

		this->unuse_Program();
	}

	void set_Mat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{
		this->use_Program();

		glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

		this->unuse_Program();
	}
};
