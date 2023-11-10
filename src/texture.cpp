#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int32_t Texture::s_slotCount = 0;

Texture::Texture(const std::string& name) {
    glGenTextures(1, &m_id);
    CORE_ASSERT(s_slotCount < (MAX_TEXTURES-1), "Texture Limit has been reached!");
    m_slot = s_slotCount++;
    glActiveTexture(GL_TEXTURE0 + m_slot);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(name.c_str(), &m_width, &m_height, &m_channels, 0);
    CORE_ASSERT(data, "Failed to load texture image");
    GLenum imageLayout = (m_channels==3) ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, imageLayout, m_width, m_height, 0, imageLayout, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_id);
    s_slotCount--;
}

void Texture::bind() const {
    glActiveTexture(GL_TEXTURE0 + m_slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}