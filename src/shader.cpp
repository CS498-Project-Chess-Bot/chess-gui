#include "shader.hpp"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexCode = readShaderFileAsStr(vertexPath);
    const char* vertexCodeCstr = vertexCode.c_str();
    std::string fragmentCode = readShaderFileAsStr(fragmentPath);
    const char* fragmentCodeCstr = fragmentCode.c_str();

    int success;
    char infoLog[512];

    uint32_t vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCodeCstr, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    uint32_t fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCodeCstr, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    programID = glCreateProgram();
    glAttachShader(programID, vertex);
    glAttachShader(programID, fragment);
    glLinkProgram(programID);

    // print linking errors if any
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(programID);
}

void Shader::bind() const {
    glUseProgram(programID);
}

const std::string Shader::readShaderFileAsStr(const std::string& path) {
    std::string shaderCode;
    std::ifstream ShaderFile;

    // ensure ifstream objects can throw exceptions:
    ShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        ShaderFile.open(path);
        std::stringstream ShaderStream;
        // read file's buffer contents into streams
        ShaderStream << ShaderFile.rdbuf();
        // close file handlers
        ShaderFile.close();
        // convert stream into string
        shaderCode = ShaderStream.str();
    }
    catch(std::ifstream::failure& e)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    
    return shaderCode;
}

uint32_t Shader::getUniformLocation(const std::string& name) {
    if(m_uniformMap.find(name) != m_uniformMap.end()) {
        return m_uniformMap[name];
    }

    int32_t location = glGetUniformLocation(programID, name.c_str());
    CORE_ASSERT(location != -1, "Uniform of this name does not exist!");
    return m_uniformMap[name] = (uint32_t)location;
}

void Shader::setInt(const std::string& name, int32_t value) {
    bind();
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setFloat(const std::string& name, float value) {
    bind();
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setFloat4(const std::string& name, const glm::vec4& values) {
    bind();
    glUniform4f(getUniformLocation(name), values.r, values.g, values.b, values.a);
}

void Shader::setMat4(const std::string& name, const glm::mat4& matrix) {
    bind();
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setTexture(const std::string& name, Texture& texture) {
    bind();
    glUniform1i(getUniformLocation(name), texture.slot());
}