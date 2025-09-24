#include "platform.h"
#include "input.h"
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


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

    Input::Init();

    while (!Platform::WindowShouldClose(window)) {
        Platform::PollEvents();
        Input::PollEvents();

        if (Input::IsKeyPressed(Input::KeyCode::Escape)) break;

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers((GLFWwindow*)window->handle);
    }

    Input::Shutdown();
    Platform::DestroyWindow(window);
    Platform::Shutdown();
    return 0;
}


