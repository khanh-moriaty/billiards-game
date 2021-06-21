#pragma once

#include <GL/glew.h>
#include <vector>
#include <objects/vertex.h>
class Primitive
{
protected:
	static const GLfloat PI;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	// Current state of initialization
	float xSegment, ySegment;
	float xPos, yPos, zPos;
	glm::vec3 normalVector;

	// Number of vertices on mesh = Xmax * Ymax
	// Define Xmax and Ymax based on primitive shapes.
	// Spheres and circles need more vertices.
	virtual int getXMax() = 0;
	virtual int getYMax() = 0;

	// Initialize vertices with position, normal vector and texture coordinate.
	virtual void initVertices();
	// Initialize indice of vertices in triangles.
	virtual void initIndices(int offset=0);

	// Calculate the position coordinate of current state.
	// This is an abstract method. Has to be defined in derived classes.
	virtual void getCoordinate() = 0;
	
	// Calculate the normal vector of current state.
	// This is an abstract method. Has to be defined in derived classes.
	virtual void getNormalVector() = 0;

	Primitive();
public:
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
protected:
	float radius;

	virtual int getXMax();
	virtual int getYMax();

	virtual void getCoordinate();
	virtual void getNormalVector();
public:
	Sphere(float radius);
};

class Cone : public Primitive
{
protected:
	static const float TOP_RATIO; // TOP_RATIO = p/h

	float radius;
	float height;
	float fullHeight;
	float top;
	float sphereRadius;

	virtual int getXMax();
	virtual int getYMax();

	virtual void getCoordinate();
	virtual void getNormalVector();
public:
	Cone(float radius, float height);
};

class Plane : public Primitive
{
protected:
	float width, height, depth;
	float z;

	virtual int getXMax();
	virtual int getYMax();

	virtual void getCoordinate();
	virtual void getNormalVector();

	virtual void initVertices();

	void generateFace(float width, float height, float z);
	void generateIndices(int offset);
public:
	Plane(float width, float height, float depth);
};