#include "texture_loader.hpp"

TextureLoader* TextureLoader::s_loader = nullptr;

TextureLoader *TextureLoader::GetInstance() {
    if(!s_loader) {
        s_loader = new TextureLoader();
    }

    return s_loader;
}

void TextureLoader::DestroyInstance() {
    if(s_loader) {
        delete s_loader;
    }
}

TextureLoader::TextureLoader() {
    for (const auto& file : std::filesystem::directory_iterator(TEXTURE_DIR)) {
        std::string texture_file = file.path().filename().string();
        m_textureMap[texture_file] = createRef<Texture>(std::string(TEXTURE_DIR) + "/" + texture_file);
    }
}

Ref<Texture> TextureLoader::retrieveTexture(const std::string& name) {
    if(m_textureMap.find(name) != m_textureMap.end()) {
        return m_textureMap[name];
    }

    CORE_ASSERT(false, "Trying to access a texture which does not exist!");
    return nullptr;
}