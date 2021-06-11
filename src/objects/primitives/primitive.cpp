#include "primitive.h"

#include <iostream>

Sphere::Sphere(float radius):Primitive()
{
	const GLfloat PI = 3.14159265358979323846f;
	const int Y_SEGMENTS = 50;
	const int X_SEGMENTS = 50;
	const float SCALE = radius;

	std::vector<Vertex> Vertices;
	std::vector<GLuint> Indices;

	for (int y = 0; y <= Y_SEGMENTS; y++)
	{
		for (int x = 0; x <= X_SEGMENTS; x++)
		{
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI) * SCALE;
			float yPos = std::cos(ySegment * PI) * SCALE;
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI) * SCALE;
			glm::vec3 pos = glm::vec3(xPos, yPos, zPos);
			glm::vec3 color = glm::vec3(0.f, 0.f, 0.f);
			glm::vec2 tex = glm::vec2(- xSegment, - ySegment);
			glm::vec3 nor = glm::normalize(glm::vec3(xPos, yPos, zPos));
			Vertex temp;
			temp.position = pos;
			temp.color = color;
			temp.texcoord = tex;
			temp.normal = nor;
			Vertices.push_back(temp);
		}
	}
	unsigned nrOfVertices = sizeof(Vertices) / sizeof(Vertex);
	//Indices that generate the ball
	for (int i = 0; i < Y_SEGMENTS; i++)
	{
		for (int j = 0; j < X_SEGMENTS; j++)
		{
			Indices.push_back(i * (X_SEGMENTS + 1) + j);
			Indices.push_back((i + 1) * (X_SEGMENTS + 1) + j);
			Indices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
			Indices.push_back(i * (X_SEGMENTS + 1) + j);
			Indices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
			Indices.push_back(i * (X_SEGMENTS + 1) + j + 1);
		}
	}
	unsigned nrOfIndices = sizeof(Indices) / sizeof(GLuint);
	this->vertices = Vertices;
	this->indices = Indices;
}

void Primitive::set(const Vertex* vertices,
	const unsigned nrOfVertices,
	const GLuint* indices,
	const unsigned nrOfIndices)
{
	for (size_t i = 0; i < nrOfVertices; i++)
	{
		this->vertices.push_back(vertices[i]);
	}

	for (size_t i = 0; i < nrOfIndices; i++)
	{
		this->indices.push_back(indices[i]);
	}
}

Vertex* Primitive::getVertices() { return this->vertices.data(); }
GLuint* Primitive::getIndices() { return this->indices.data(); }
const unsigned Primitive::getNrOfVertices() { return this->vertices.size(); }
const unsigned Primitive::getNrOfIndices() { return this->indices.size(); }
