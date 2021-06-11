#pragma once
#include <vector>
#include "vertex.h"
#include "primitives/primitive.h"
#include "shaders/shader.h"
#include "texture/texture.h"

class Mesh
{
private:
	Vertex* vertexArray;
	unsigned nrOfVertices;
	GLuint* indexArray;
	unsigned nrOfIndices;

	Texture* texture;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 origin;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 ModelMatrix;

	void updateUniforms(Shader* shader) {shader->set_Mat4fv(this->ModelMatrix, "ModelMatrix");}

	void initVAO();

	void updateModelMatrix();

public:
	Mesh(
		Vertex* vertexArray,
		const unsigned& nrOfVertices,
		GLuint* indexArray,
		const unsigned& nrOfIndices,
		Texture* texture,
		glm::vec3 position,
		glm::vec3 origin = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f));

	Mesh(
		Primitive* primitive,
		Texture* texture,
		glm::vec3 position,
		glm::vec3 origin = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f));

	Mesh(const Mesh& obj);

	Mesh(
		std::vector<Vertex> vertexArray,
		Texture* texture,
		glm::vec3 position,
		glm::vec3 origin = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f)
	): Mesh(vertexArray.data(), vertexArray.size(), NULL, 0, texture, position, origin, rotation, scale) {}

	~Mesh();

	void render(Shader* shader);

	//Accessors

	//Modifiers
	void setPosition(const glm::vec3 position) {this->position = position;}
	void setOrigin(const glm::vec3 origin) {this->origin = origin;}
	void setRotation(const glm::vec3 rotation) {this->rotation = rotation;}
	void setScale(const glm::vec3 scale) {this->scale = scale;}

	//Functions

	void move(const glm::vec3 position) {this->position += position;}
	void rotate(const glm::vec3 rotation) {this->rotation += rotation;}
	void scaleUp(const glm::vec3 scale) {this->scale += scale;}

	void update() {}
};