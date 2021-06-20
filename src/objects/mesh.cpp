#pragma once
#include "mesh.h"
#include <glm/gtc/matrix_transform.hpp>

const GLfloat Mesh::SHININESS = 1.f;

Mesh::Mesh(
	Vertex *vertexArray,
	const unsigned &nrOfVertices,
	GLuint *indexArray,
	const unsigned &nrOfIndices,
	Texture *texture,
	glm::vec3 position,
	glm::vec3 origin,
	glm::vec3 rotation,
	glm::vec3 scale)
{
	this->position = position;
	this->origin = origin;
	this->rotation = rotation;
	this->scale = scale;

	this->texture = texture;
	this->shininess = SHININESS;

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

Mesh::Mesh(
	Primitive *primitive,
	Texture *texture,
	glm::vec3 position,
	glm::vec3 origin,
	glm::vec3 rotation,
	glm::vec3 scale)
{
	this->position = position;
	this->origin = origin;
	this->rotation = rotation;
	this->scale = scale;

	this->texture = texture;
	this->shininess = SHININESS;

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

Mesh::Mesh(const Mesh &obj)
{
	this->position = obj.position;
	this->origin = obj.origin;
	this->rotation = obj.rotation;
	this->scale = obj.scale;

	this->texture = obj.texture;
	this->shininess = SHININESS;

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

Mesh::~Mesh()
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

void Mesh::updateUniforms(Shader *shader)
{
	shader->set_Mat4fv(this->ModelMatrix, "ModelMatrix");
	shader->set_1f(this->shininess, "shininess");
}

void Mesh::initVAO()
{
	//Create VAO
	glCreateVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	//GEN VBO AND BIND AND SEND DATA
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), this->vertexArray, GL_STATIC_DRAW);

	//GEN EBO AND BIND AND SEND DATA
	if (this->nrOfIndices > 0)
	{
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), this->indexArray, GL_STATIC_DRAW);
	}

	//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	//Texcoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);
	//Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	//BIND VAO 0
	glBindVertexArray(0);
}

void Mesh::move(const glm::vec3 displacement)
{
	this->position += displacement;
	// this->origin += displacement;
}
void Mesh::rotate(const glm::vec3 rotation)
{
	this->rotation += rotation;
}
void Mesh::scaleUp(const glm::vec3 scale)
{
	this->scale += scale;
}

#include <stdio.h>
void Mesh::updateModelMatrix()
{
	this->ModelMatrix = glm::mat4(1.f);
	this->ModelMatrix = glm::translate(this->ModelMatrix, this->origin);
	this->ModelMatrix = glm::translate(this->ModelMatrix, this->position - this->origin);

	// Calculate orthogonal unit vector (Rx, Ry, Rz)
	glm::vec3 R(1.f);
	if (glm::length(this->rotation) > 0)
	{
		if (this->rotation.x == 0.f && this->rotation.z == 0.f)
		{
			R = glm::vec3(0.f, 1.f, 0.f);
		}
		else
		{
			R = glm::cross(this->rotation, glm::vec3(0.f, 1.f, 0.f));
			R = glm::normalize(R);
		}
	}

	// Calculate theta
	float theta = -glm::length(this->rotation);
	float cos = std::cos(theta);
	float sin = std::sin(theta);

	this->ModelMatrix = glm::rotate(this->ModelMatrix, theta, R);

	this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
}

void Mesh::render(Shader *shader)
{
	// set texture
	shader->set_1i(this->texture->getunit(), "_texture");
	this->texture->bind();

	//Update uniforms
	this->updateModelMatrix();
	this->updateUniforms(shader);

	//Bind VAO
	glBindVertexArray(this->VAO);

	//RENDER
	if (this->nrOfIndices == 0)
		glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices);
	else
		glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);

	//Cleanup
	// glBindVertexArray(0);
	// glUseProgram(0);
	// glActiveTexture(0);
	// glBindTexture(GL_TEXTURE_2D, 0);
}