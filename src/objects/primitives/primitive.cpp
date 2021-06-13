#include "primitive.h"

const GLfloat Primitive::PI = 3.14159265358979323846f;
const int Primitive::X_SEGMENTS = 50;
const int Primitive::Y_SEGMENTS = 50;

void Primitive::generateIndices(int offset){
	for (int i = 0; i < Y_SEGMENTS; i++)
	{
		for (int j = 0; j < X_SEGMENTS; j++)
		{
			this->indices.push_back(offset + i * (X_SEGMENTS + 1) + j);
			this->indices.push_back(offset + (i + 1) * (X_SEGMENTS + 1) + j);
			this->indices.push_back(offset + (i + 1) * (X_SEGMENTS + 1) + j + 1);
			this->indices.push_back(offset + i * (X_SEGMENTS + 1) + j);
			this->indices.push_back(offset + (i + 1) * (X_SEGMENTS + 1) + j + 1);
			this->indices.push_back(offset + i * (X_SEGMENTS + 1) + j + 1);
		}
	}
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
