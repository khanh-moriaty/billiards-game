#include "texture.h"

#include <iostream>
#include <string>
#include <SOIL2.h>

Texture::Texture(const char* fileName, GLenum type, GLint texture_unit)
{
	this->type = type;
	this->texture_unit = texture_unit;

	unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);
	glGenTextures(1, &this->id);
	glBindTexture(type, this->id);
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (image)
	{
		glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(type);
	}
	else
	{
		std::cout << "ERROR cant load texture" << fileName << "\n";
	}

	glActiveTexture(0);
	glBindTexture(type, 0);
	SOIL_free_image_data(image);
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0 + this->texture_unit);
	glBindTexture(this->type, this->id);
}

void Texture::unbind()
{
	glActiveTexture(0);
	glBindTexture(this->type, 0);
}

void Texture::loadFromFile(const char* fileName)
{
	if (this->id)
	{
		glDeleteTextures(1, &this->id);
	}

	unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

	glGenTextures(1, &this->id);
	glBindTexture(this->type, this->id);

	glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (image)
	{
		glTexImage2D(this->type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(this->type);
	}
	else
	{
		std::cout << "ERROR::TEXTURE::LOADFROMFILE::TEXTURE_LOADING_FAILED: " << fileName << "\n";
	}

	glActiveTexture(0);
	glBindTexture(this->type, 0);
	SOIL_free_image_data(image);
}