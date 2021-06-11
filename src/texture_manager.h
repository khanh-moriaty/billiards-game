#include "texture.h"
#include <unordered_map>

class TextureManager
{
private:
    std::unordered_map<const char*, Texture> textureList;

public:
    TextureManager();
};