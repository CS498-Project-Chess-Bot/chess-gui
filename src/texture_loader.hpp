#ifndef TEXTURELOADER_HPP
#define TEXTURELOADER_HPP

#include "core.hpp"
#include "texture.hpp"

const char* TEXTURE_DIR = "textures";

class TextureLoader {
protected:
    TextureLoader();
    static TextureLoader* s_loader;

public:
    TextureLoader(TextureLoader &other) = delete;
    void operator=(const TextureLoader&) = delete;

    Ref<Texture> retrieveTexture(const std::string& name);

    static TextureLoader* GetInstance();
    static void DestroyInstance();

private:
    std::unordered_map<std::string, Ref<Texture>> m_textureMap;

};


#endif