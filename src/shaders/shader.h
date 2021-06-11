#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

class Shader
{
private:
	GLuint id;
	GLuint load_Shader(GLenum type,const char* filename);
	void link_Program(unsigned int vertexShader, unsigned int fragmentShader, unsigned int geometryShader);

public:
	Shader(){}
	Shader(const Shader &a)
	{
		this->id = a.id;
	}
	Shader(const char* vertex_file, const char* fragment_file, const char* geometry_file = nullptr);
	
	~Shader();

	void operator=(const Shader& a) {this->id = a.id;}

	GLint getid()
	{
		return this->id;
	}

	void use_Program();

	void unuse_Program();

	//set uniform function
	void set_1i(GLint value, const GLchar* name);
	void set_1f(GLfloat value, const GLchar* name);
	void set_2fv(glm::fvec2 value, const GLchar* name);
	void set_3fv(glm::fvec3 value, const GLchar* name);
	void set_4fv(glm::fvec4 value, const GLchar* name);
	void set_Mat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);
	void set_Mat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);
};
