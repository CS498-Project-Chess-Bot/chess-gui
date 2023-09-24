#include "core.hpp"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(void)
{
    // glfw window creation
    // --------------------
    App app(SCR_WIDTH, SCR_HEIGHT, "chess-gui");

    int result = app.run();

    if(result != 0) {
        std::cerr << "App failed to close cleanly!\n";
    }

    return result;

    
}

