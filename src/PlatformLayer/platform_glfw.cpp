#include "platform.h"
#include <GLFW/glfw3.h>

static double lastFrameTime = 0.0;
static double deltaTime = 0.0;

namespace Platform {
    bool Init() {
        return glfwInit() == GLFW_TRUE;
    }

    void Shutdown() {
        glfwTerminate();
    }

    Window* CreateWindow(int width, int height, const char* title) {
        GLFWwindow* glfwWin = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!glfwWin) return nullptr;

        auto* w = new Window{ glfwWin, width, height };
        glfwMakeContextCurrent(glfwWin);
        return w;
    }

    void DestroyWindow(Window* window) {
        if (window) {
            glfwDestroyWindow((GLFWwindow*)window->handle);
            delete window;
        }
    }

    void PollEvents() {
        glfwPollEvents();
        double now = glfwGetTime();
        deltaTime = now - lastFrameTime;
        lastFrameTime = now;
    }

    bool WindowShouldClose(Window* window) {
        return glfwWindowShouldClose((GLFWwindow*)window->handle);
    }

    double GetTimeSeconds() {
        return glfwGetTime();
    }

    double GetDeltaTime() {
        return deltaTime;
    }

    bool IsKeyDown(int key) {
        return glfwGetKey((GLFWwindow*)glfwGetCurrentContext(), key) == GLFW_PRESS;
    }
}

