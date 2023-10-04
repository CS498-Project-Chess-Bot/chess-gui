#include "core.hpp"
#include "app.hpp"
#include "renderer.hpp"
#include "camera.hpp"
#include "chess_piece_2D.hpp"

uint32_t App::s_height = 0;
uint32_t App::s_width = 0;

App::App(int width, int height, const std::string title) 
{
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
    s_width = width;
    s_height = height;

}

int App::run() {
    // Shader shader("shaders/chess_piece.vs", "shaders/chess_piece.fs");
    // Texture texture("textures/chess_white_pawn.png");
    // shader.setTexture("textureSlot", texture);
    

    // std::vector<float> vertices = {
    //      0.5f,  0.5f, 0.0f,     1.0f, 1.0f, // top right
    //      0.5f, -0.5f, 0.0f,     1.0f, 0.0f, // bottom right
    //     -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, // bottom left
    //     -0.5f,  0.5f, 0.0f,     0.0f, 1.0f // top left 
    // };
    // VertexBuffer VBO(vertices);
    // BufferLayout layout = {
    //     BufferElement(ShaderDataType::Float3, "Position"),
    //     BufferElement(ShaderDataType::Float2, "TexCoord")
    // };
    // VBO.setLayout(layout);


    // std::vector<uint32_t> indices = {  // note that we start from 0!
    //     0, 1, 3,  // first Triangle
    //     1, 2, 3   // second Triangle
    // };
    // IndexBuffer IBO(indices);

    // VertexArray VAO;
    // VAO.addVertexBuffer(VBO);
    // VAO.setIndexBuffer(IBO);

    //glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.0f));
    ChessPieceModel2D whitePawn(ChessPieceType::white_pawn);
    whitePawn.transform().changePos({0.0f, 1.0f, 0.0f});
    whitePawn.transform().changeScale({0.5f, 0.5f, 1.0f});

    Camera camera({0.0f, 0.0f, 5.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f});

    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput();

        // render
        

        RenderCommand::beginScene(camera);
        RenderCommand::clear(0.2f, 0.3f, 0.3f, 1.0f);
        RenderCommand::submit(whitePawn);
        RenderCommand::endScene();
        
        //glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)s_width/(float)s_height, 0.1f, 100.0f);
        //glm::mat4 projection = glm::mat4(1.0f);
        //shader.setMat4("projection", projection);

        //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        //std::cout << camera.view()[3][3] << std:: endl;
        //shader.setMat4("view", camera.view());

        //glDrawArrays(GL_TRIANGLES, 0, 6);
        // RenderCommand::submit(VAO, shader, texture);
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
    App::s_width = width;
    App::s_height = height;
}