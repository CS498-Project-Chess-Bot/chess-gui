#ifndef SHADER_HPP
#define SHADER_HPP

#include "core.hpp"

class Shader {
public:
    Shader() = delete;
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();



    void bind() const;

private:
    const std::string readShaderFileAsStr(const std::string& path);

private:
    uint32_t programID;

};

#endif

