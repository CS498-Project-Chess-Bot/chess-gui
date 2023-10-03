#ifndef SHADER_HPP
#define SHADER_HPP

#include "core.hpp"
#include "texture.hpp"
#include <unordered_map>

class Shader {
public:
    Shader() = delete;
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void bind() const;

    void setInt(const std::string& name, int32_t value);

    void setFloat(const std::string& name, float value);

    void setTexture(const std::string& name, Texture& texture);


private:
    const std::string readShaderFileAsStr(const std::string& path);
    uint32_t getUniformLocation(const std::string& name);

private:
    std::unordered_map<std::string, uint32_t> m_uniformMap;
    uint32_t programID;


};

#endif

