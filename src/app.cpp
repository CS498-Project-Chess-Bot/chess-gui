#include "core.hpp"
#include "app.hpp"
#include "renderer.hpp"
#include "camera.hpp"
#include "chess_board_2D.hpp"
#include "timestep.hpp"
#include "texture_loader.hpp"
#include "board.hpp"
#include "command.hpp"

uint32_t App::s_height = 0;
uint32_t App::s_width = 0;
static bool shouldResetGame = true;

static glm::vec3 mousePosToWorld(double& x, double& y, Camera cam, glm::mat4 proj, int screenWidth, int screenHeight);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods); 

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

    glfwSetKeyCallback(window, (GLFWkeyfun) key_callback);

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

    srand(time(NULL));
}

int App::run() {

    Ref<ChessBoardModel2D> chessBoard;

    Camera camera({3.5f, 3.5f, 5.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f});

    bool firstTileSelected = false;
    int firstTileX = -1, firstTileY = -1;

    std::future<CommandResult> engineResult;
    engineResult = std::async(Command::exec, "python ./chess-engine/Game.py");
    while (!glfwWindowShouldClose(window))
    {
        processInput();
        if(shouldResetGame) {
            chessBoard = createRef<ChessBoardModel2D>((bool)(rand()%2));
            shouldResetGame = false;
        }

        std::future_status engineStatus = engineResult.wait_for(std::chrono::seconds(0));
        if(engineStatus == std::future_status::ready) {
            CommandResult r = engineResult.get();
            std::cout << r << std::endl;
            engineResult = std::async(Command::exec, "python ./chess-engine/Game.py");
        }

        if(m_mousePressed_x != -1 && m_mousePressed_y != -1) {
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)s_width/(float)s_height, 0.1f, 100.0f);
            glm::vec3 mouseWorld = mousePosToWorld(m_mousePressed_x, m_mousePressed_y, camera, projection, s_width, s_height);
            glm::vec3 raydir = camera.pos() - mouseWorld;

            int tileX, tileY;
            bool hits = chessBoard->getHitTile(camera, raydir, &tileX, &tileY);
            if(hits) {
                if(!firstTileSelected) {
                    chessBoard->clearHightlighting();
                    firstTileSelected = true;
                    firstTileX = tileX;
                    firstTileY = tileY;
                }
                else {
                    chessBoard->setTileHightlight(firstTileX, firstTileY, false);
                    if(chessBoard->tryMove(Move(firstTileX, firstTileY, tileX, tileY, chessBoard->getGameBoard().getBoardState().at(firstTileY*8 + firstTileX)))) {
                        firstTileSelected = false;
                    }
                    else {
                        firstTileX = tileX;
                        firstTileY = tileY;
                    }
                    
                }
                chessBoard->setTileHightlight(tileX, tileY, true);
            }

        }

        float time = (float)glfwGetTime();
		Timestep deltaTime = time - m_lastFrameTime;
		m_lastFrameTime = time;
        (void)deltaTime;

        
        // render

        RenderCommand::beginScene(camera);
        RenderCommand::clear(0.2f, 0.3f, 0.3f, 1.0f);
        Ref<Object> boardObject = std::dynamic_pointer_cast<Object>(chessBoard);
        RenderCommand::submit(boardObject);
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
    glfwPollEvents();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    m_mousePressed_x = -1;
    m_mousePressed_y = -1;
    int currentMouseState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if(currentMouseState == GLFW_RELEASE && m_oldMouseState == GLFW_PRESS) {
        glfwGetCursorPos(window, &m_mousePressed_x, &m_mousePressed_y);
    }
    m_oldMouseState = currentMouseState;


}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    RenderCommand::setViewport(width, height);
    App::s_width = width;
    App::s_height = height;
}

static glm::vec3 mousePosToWorld(double& x, double& y, Camera cam, glm::mat4 proj, int screenWidth, int screenHeight) {
    glm::mat4 invMat = glm::inverse(proj * cam.view());

    double normalizedX = x / (screenWidth/2) - 1;
    double normalizedY = -(y / (screenHeight/2) - 1);

    double z = cam.pos().z + cam.forward().z;
    glm::vec4 mousePos = {normalizedX, normalizedY, z, 1};

    mousePos = invMat * mousePos;
    mousePos /= mousePos.w;
    return glm::vec3(mousePos.x, mousePos.y, mousePos.z);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
        shouldResetGame = true;
}