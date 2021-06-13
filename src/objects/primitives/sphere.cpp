#include "primitive.h"

Sphere::Sphere(float radius):Primitive()
{
	const float scale = radius;

	std::vector<Vertex> Vertices;
	std::vector<GLuint> Indices;

	for (int y = 0; y <= Y_SEGMENTS; y++)
	{
		for (int x = 0; x <= X_SEGMENTS; x++)
		{
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI) * scale;
			float yPos = std::cos(ySegment * PI) * scale;
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI) * scale;
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