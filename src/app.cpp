#include "core.hpp"
#include "app.hpp"
#include "renderer.hpp"


App::App(int width, int height, const std::string title) {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "ERROR::APP::FAILED TO CREATE GLFW WINDOW" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, (GLFWframebuffersizefun)framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "ERROR::APP::FAILED TO INIT GLAD" << std::endl;
        exit(-1);
    } 

    RenderCommand::init();

}

int App::run() {
    Shader shader("shaders/flat.vs", "shaders/flat.fs");
    

    std::vector<float> vertices = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    VertexBuffer VBO(vertices);
    BufferLayout layout = {
        BufferElement(ShaderDataType::Float3, "Position")
    };
    VBO.setLayout(layout);


    std::vector<uint32_t> indices = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    IndexBuffer IBO(indices);

    VertexArray VAO;
    VAO.addVertexBuffer(VBO);
    VAO.setIndexBuffer(IBO);

    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput();

        // render
        RenderCommand::clear(0.2f, 0.3f, 0.3f, 1.0f);
        // draw our first triangle
        shader.bind();
        VAO.bind();
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        RenderCommand::submit(VAO);
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    RenderCommand::exit();
    glfwTerminate();
    return 0;
}

void App::processInput() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    RenderCommand::setViewport(width, height);
}