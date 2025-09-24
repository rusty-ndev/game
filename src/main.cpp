#include "platform.h"
#include <GLFW/glfw3.h> // for key definitions
#include <iostream>

int main() {
    if (!Platform::Init()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    auto* window = Platform::CreateWindow(1280, 720, "My Game");
    if (!window) {
        std::cerr << "Failed to create window\n";
        Platform::Shutdown();
        return -1;
    }

    // Main loop
    while (!Platform::WindowShouldClose(window)) {
        Platform::PollEvents();

        if (Platform::IsKeyDown(GLFW_KEY_ESCAPE)) break;

        // Clear screen (OpenGL for now)
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers
        glfwSwapBuffers((GLFWwindow*)window->handle);
    }

    Platform::DestroyWindow(window);
    Platform::Shutdown();
    return 0;
}

