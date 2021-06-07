#pragma once
#include<iostream>
#include<vector>
#include "vertex.h"
#include "primitives.h"
#include "shaders/shader.h"
#include "texture.h"
#include "material.h"

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

	void initVAO();

	void updateUniforms(Shader* shader);

	void updateModelMatrix();

public:
	Mesh(
		Vertex* vertexArray,
		const unsigned& nrOfVertices,
		GLuint* indexArray,
		const unsigned& nrOfIndices,
		Texture* texture,
		glm::vec3 position = glm::vec3(0.f),
		glm::vec3 origin = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f))
	{
		this->position = position;
		this->origin = origin;
		this->rotation = rotation;
		this->scale = scale;

		this->texture = texture;

		this->nrOfVertices = nrOfVertices;
		this->nrOfIndices = nrOfIndices;

		this->vertexArray = new Vertex[this->nrOfVertices];
		for (size_t i = 0; i < nrOfVertices; i++)
		{
			this->vertexArray[i] = vertexArray[i];
		}

		this->indexArray = new GLuint[this->nrOfIndices];
		for (size_t i = 0; i < nrOfIndices; i++)
		{
			this->indexArray[i] = indexArray[i];
		}

		this->initVAO();
		this->updateModelMatrix();
	}

	Mesh(
		Primitive* primitive,
		Texture* texture,
		glm::vec3 position = glm::vec3(0.f),
		glm::vec3 origin = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f))
	{
		this->position = position;
		this->origin = origin;
		this->rotation = rotation;
		this->scale = scale;

		this->texture = texture;

		this->nrOfVertices = primitive->getNrOfVertices();
		this->nrOfIndices = primitive->getNrOfIndices();

		this->vertexArray = new Vertex[this->nrOfVertices];
		for (size_t i = 0; i < this->nrOfVertices; i++)
		{
			this->vertexArray[i] = primitive->getVertices()[i];
		}

		this->indexArray = new GLuint[this->nrOfIndices];
		for (size_t i = 0; i < this->nrOfIndices; i++)
		{
			this->indexArray[i] = primitive->getIndices()[i];
		}

		this->initVAO();
		this->updateModelMatrix();
	}

	Mesh(const Mesh& obj)
	{
		this->position = obj.position;
		this->origin = obj.origin;
		this->rotation = obj.rotation;
		this->scale = obj.scale;

		this->texture = obj.texture;

		this->nrOfVertices = obj.nrOfVertices;
		this->nrOfIndices = obj.nrOfIndices;

		this->vertexArray = new Vertex[this->nrOfVertices];
		for (size_t i = 0; i < this->nrOfVertices; i++)
		{
			this->vertexArray[i] = obj.vertexArray[i];
		}

		this->indexArray = new GLuint[this->nrOfIndices];
		for (size_t i = 0; i < this->nrOfIndices; i++)
		{
			this->indexArray[i] = obj.indexArray[i];
		}

		this->initVAO();
		this->updateModelMatrix();
	}

	~Mesh()
	{
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);

		if (this->nrOfIndices > 0)
		{
			glDeleteBuffers(1, &this->EBO);
		}

		delete[] this->vertexArray;
		delete[] this->indexArray;
	}

	//Accessors

	//Modifiers
	void setPosition(const glm::vec3 position);

	void setOrigin(const glm::vec3 origin);

	void setRotation(const glm::vec3 rotation);

	void setScale(const glm::vec3 setScale);

	//Functions

	void move(const glm::vec3 position);
	void rotate(const glm::vec3 rotation);
	void scaleUp(const glm::vec3 scale);

	void update();

	void render(Shader* shader);
};