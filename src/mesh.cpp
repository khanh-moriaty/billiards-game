#pragma once
#include "Mesh.h"

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	//Texcoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);
	//Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	//BIND VAO 0
	glBindVertexArray(0);
}

void Mesh::updateUniforms(Shader* shader)
{
	shader->set_Mat4fv(this->ModelMatrix, "ModelMatrix");
}

void Mesh::updateModelMatrix()
{
	this->ModelMatrix = glm::mat4(1.f);
	this->ModelMatrix = glm::translate(this->ModelMatrix, this->origin);
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
	this->ModelMatrix = glm::translate(this->ModelMatrix, this->position - this->origin);
	this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
}
//Modifiers
void Mesh::setPosition(const glm::vec3 position)
{
	this->position = position;
}

void Mesh::setOrigin(const glm::vec3 origin)
{
	this->origin = origin;
}

void Mesh::setRotation(const glm::vec3 rotation)
{
	this->rotation = rotation;
}

void Mesh::setScale(const glm::vec3 setScale)
{
	this->scale = scale;
}

//Functions

void Mesh::move(const glm::vec3 position)
{
	this->position += position;
}

void Mesh::rotate(const glm::vec3 rotation)
{
	this->rotation += rotation;
}

void Mesh::scaleUp(const glm::vec3 scale)
{
	this->scale += scale;
}

void Mesh::update()
{

}

void Mesh::render(Shader* shader)
{
	// set texture
	shader->set_1i(this->texture->getunit(), "_texture");
	this->texture->bind();

	//Update uniforms
	this->updateModelMatrix();
	this->updateUniforms(shader);

	shader->use_Program();

	//Bind VAO
	glBindVertexArray(this->VAO);

	//RENDER
	if (this->nrOfIndices == 0)
		glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices);
	else
		glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);

	//Cleanup
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}