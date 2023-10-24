#include "core.hpp"
#include "app.hpp"
#include "renderer.hpp"
#include "camera.hpp"
#include "chess_piece_2D.hpp"
#include "chess_tile_2D.hpp"
#include "timestep.hpp"
#include "texture_loader.hpp"

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
    TextureLoader::GetInstance();
    s_width = width;
    s_height = height;

}

int App::run() {
    using enum ChessPieceType;
    std::vector<ChessPieceType> boardState = {
        white_rook, white_knight, white_bishop, white_queen, white_king, white_bishop, white_knight, white_rook,
        white_pawn, white_pawn,   white_pawn,   white_pawn,  white_pawn, white_pawn,   white_pawn,   white_pawn,
        none,       none,         none,         none,        none,       none,         none,         none,
        none,       none,         none,         none,        none,       none,         none,         none,
        none,       none,         none,         none,        none,       none,         none,         none,
        none,       none,         none,         none,        none,       none,         none,         none,
        black_pawn, black_pawn,   black_pawn,   black_pawn,  black_pawn, black_pawn,   black_pawn,   black_pawn,
        black_rook, black_knight, black_bishop, black_queen, black_king, black_bishop, black_knight, black_rook,
    };


    std::vector<Ref<Object>> boardModel;
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            bool isWhite = ((y*8)+x+(y%2))%2;
            Ref<Object> tile = createRef<ChessTileModel2D>(isWhite);
            tile->transform().changePos({x*1.0f, y*1.0f, -8.0f});

            int idx = 8*y + x;
            if(boardState[idx] != none){
                Ref<Object> piece = createRef<ChessPieceModel2D>(boardState[idx]);
                tile->addChild(piece);
            }
            boardModel.push_back(tile);
        }
    }

    Camera camera({3.5f, 3.5f, 5.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f});

    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput();

        float time = (float)glfwGetTime();
		Timestep deltaTime = time - m_lastFrameTime;
		m_lastFrameTime = time;
        (void)deltaTime;

        
        // render

        RenderCommand::beginScene(camera);
        RenderCommand::clear(0.2f, 0.3f, 0.3f, 1.0f);
        for(auto& tile : boardModel) {
            RenderCommand::submit(tile);
        }
        RenderCommand::endScene(s_width, s_height);

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