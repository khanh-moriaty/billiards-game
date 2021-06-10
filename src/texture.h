#pragma once

#include <GL/glew.h>
// #include <GLFW/glfw3.h>

class Texture
{
private:
	unsigned int id;
	int width;
	int height;
	GLenum type;
	GLint texture_unit;

public:
	Texture(){};

	Texture(const char *fileName, GLenum type, GLint texture_unit);

	~Texture() { glDeleteTextures(1, &this->id); }

	inline GLuint getID() const { return this->id; }
	GLint getunit() { return this->texture_unit; }
	void bind();
	void unbind();
	void loadFromFile(const char *fileName);
};
