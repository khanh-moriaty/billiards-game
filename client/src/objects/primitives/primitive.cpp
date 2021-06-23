#include "primitive.h"

const GLfloat Primitive::PI = 3.14159265358979323846f;

Primitive::Primitive(){}

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

void Primitive::initVertices() {
	for (int y = 0; y < getYMax(); y++)
	{
		for (int x = 0; x < getXMax(); x++)
		{
			xSegment = (float)x / (float)(getXMax()-1);
			ySegment = (float)y / (float)(getYMax()-1);
			getCoordinate();
			getNormalVector();
			glm::vec3 pos = glm::vec3(xPos, yPos, zPos);
			glm::vec3 color = glm::vec3(0.f, 0.f, 0.f);
			glm::vec2 tex = glm::vec2(- xSegment, ySegment);
			glm::vec3 nor = normalVector;
			Vertex temp;
			temp.position = pos;
			temp.color = color;
			temp.texcoord = tex;
			temp.normal = nor;
			this->vertices.push_back(temp);
		}
	}
}

void Primitive::initIndices(int offset) {
	for (int i = 0; i < getYMax() - 1; i++)
	{
		for (int j = 0; j < getXMax() - 1; j++)
		{
			this->indices.push_back(offset + i * getXMax() + j);
			this->indices.push_back(offset + (i + 1) * getXMax() + j);
			this->indices.push_back(offset + (i + 1) * getXMax() + j + 1);
			this->indices.push_back(offset + i * getXMax() + j);
			this->indices.push_back(offset + (i + 1) * getXMax() + j + 1);
			this->indices.push_back(offset + i * getXMax() + j + 1);
		}
	}
}

Vertex* Primitive::getVertices() { return this->vertices.data(); }
GLuint* Primitive::getIndices() { return this->indices.data(); }
const unsigned Primitive::getNrOfVertices() { return this->vertices.size(); }
const unsigned Primitive::getNrOfIndices() { return this->indices.size(); }
