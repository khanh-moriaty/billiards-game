#include <unordered_map>
#include <string>

#include "texture.h"

#include <GL/glew.h>

class TextureManager
{
private:
    std::unordered_map<std::string, Texture*> textureList;
    GLint textureCount;

public:
    TextureManager();
    ~TextureManager();

    void initTexture();

    void addTexture2D(std::string name, const char* fileName);
    Texture* get(std::string name);
    Texture* operator[](std::string name) {return this->get(name);}
};