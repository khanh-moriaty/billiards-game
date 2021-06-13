#pragma once

#include <GL/glew.h>
#include <vector>
#include <objects/vertex.h>
class Primitive
{
public:
	static const GLfloat PI;
	static const int X_SEGMENTS;
	static const int Y_SEGMENTS;

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;


	Primitive() {}
	virtual ~Primitive() {}

	//Functions
	void set(const Vertex* vertices,
		const unsigned nrOfVertices,
		const GLuint* indices,
		const unsigned nrOfIndices);
	

	Vertex* getVertices();
	GLuint* getIndices();
	const unsigned getNrOfVertices();
	const unsigned getNrOfIndices();
};

class Sphere : public Primitive
{
public:
	Sphere(float radius);
};

class Cone : public Primitive
{
private:
	void generateConeLayer(float radius, float height);
public:
	Cone(float radius, float height);
};