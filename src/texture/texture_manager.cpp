#include "texture_manager.h"

TextureManager::TextureManager()
{
    this->textureCount = 0;
}

TextureManager::~TextureManager()
{
    for(auto x: this->textureList){
        delete x.second;
    }
}

void TextureManager::addTexture2D(const char *name, const char *fileName)
{
    Texture* texture = new Texture(fileName, GL_TEXTURE_2D, this->textureCount++);
    this->textureList[name] = texture;
}

Texture* TextureManager::operator[](const char *name)
{
    return this->textureList[name];
}