#ifndef APP_HPP
#define APP_HPP

#include "core.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class App {
public:
    App(int width, int height, const std::string title);

    int run();

private:
    void processInput();
    
private:
    GLFWwindow* window;

public:
    static uint32_t s_width, s_height;
    float m_lastFrameTime = 0;

};

#endif