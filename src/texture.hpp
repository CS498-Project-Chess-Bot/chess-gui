#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "core.hpp"

#define MAX_TEXTURES 16

class Texture {
public:
    Texture(const std::string& name);
    ~Texture();

    void bind() const;

    inline int32_t slot() const { return m_slot; }

private:
    uint32_t m_id;
    int32_t m_slot;
    int32_t m_width, m_height;
    int32_t m_channels;

    static int32_t s_slotCount;
};

#endif