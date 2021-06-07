#pragma once
#include "Primitives.h"

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
