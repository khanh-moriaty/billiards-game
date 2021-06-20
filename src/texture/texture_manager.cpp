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

void TextureManager::initTexture(){
    this->addTexture2D("wall", "res/texture/wall4.jpg");
    this->addTexture2D("floor", "res/texture/floor.png");
    this->addTexture2D("door", "res/texture/door.jpg");
    this->addTexture2D("pic", "res/texture/pic.jpg");
    this->addTexture2D("green", "res/texture/green.jpg");
    this->addTexture2D("body_wood", "res/texture/body_wood.jpg");
    this->addTexture2D("leg", "res/texture/leg.jpg");
    this->addTexture2D("light", "res/texture/light.jpg");
    this->addTexture2D("white", "res/texture/white.jpg");

    this->addTexture2D("ball0", "res/texture/ball0.jpg");
    this->addTexture2D("ball1", "res/texture/ball1.jpg");
    this->addTexture2D("ball2", "res/texture/ball2.jpg");
    this->addTexture2D("ball3", "res/texture/ball3.jpg");
    this->addTexture2D("ball4", "res/texture/ball4.jpg");
    this->addTexture2D("ball5", "res/texture/ball5.jpg");
    this->addTexture2D("ball6", "res/texture/ball6.jpg");
    this->addTexture2D("ball7", "res/texture/ball7.jpg");
    this->addTexture2D("ball8", "res/texture/ball8.jpg");
    this->addTexture2D("ball9", "res/texture/ball9.jpg");
    this->addTexture2D("ball10", "res/texture/ball10.jpg");
    this->addTexture2D("ball11", "res/texture/ball11.jpg");
    this->addTexture2D("ball12", "res/texture/ball12.jpg");
    this->addTexture2D("ball13", "res/texture/ball13.jpg");
    this->addTexture2D("ball14", "res/texture/ball14.jpg");
    this->addTexture2D("ball15", "res/texture/ball15.jpg");
}

void TextureManager::addTexture2D(std::string name, const char *fileName)
{
    Texture* texture = new Texture(fileName, GL_TEXTURE_2D, this->textureCount++);
    this->textureList[name] = texture;
}

Texture* TextureManager::get(std::string name)
{
    return this->textureList[name];
}