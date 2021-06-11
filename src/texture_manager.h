#include "texture.h"
#include <unordered_map>
#include <string>

class TextureManager
{
private:
    std::unordered_map<std::string, Texture*> textureList;
    int textureCount;

public:
    TextureManager();
    ~TextureManager();

    void addTexture2D(const char* name, const char* fileName);
    Texture* get(const char* name);
};