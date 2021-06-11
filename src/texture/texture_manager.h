#include <unordered_map>
#include <string>

#include "texture.h"

class TextureManager
{
private:
    std::unordered_map<std::string, Texture*> textureList;
    int textureCount;

public:
    TextureManager();
    ~TextureManager();

    void addTexture2D(const char* name, const char* fileName);
    Texture* operator[](const char* name);
};