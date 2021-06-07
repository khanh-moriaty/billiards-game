#pragma once
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "shaders/shader.h"



class Material
{
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLint diffuseTex;
	GLint specularTex;
public:
	Material(glm::vec3 ambient,
		glm::vec3 diffuse,
		glm::vec3 specular,
		GLint diffuseTex,
		GLint specularTex)
	{
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->diffuseTex = diffuseTex;
		this->specularTex = specularTex;

	}

	~Material(){}

	void send_to_Shader(Shader& program)
	{
		program.set_3fv(this->ambient, "material.ambient");
		program.set_3fv(this->diffuse, "material.diffuse");
		program.set_3fv(this->specular, "material.specular");
		program.set_1i(this->diffuseTex, "material.diffuseTex");
		program.set_1i(this->specularTex, "material.specularTex");
	}
};