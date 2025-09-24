#pragma once

namespace Platform {
    struct Window {
        void* handle; // actually a GLFWwindow*
        int width;
        int height;
    };

    bool Init();
    void Shutdown();

    Window* CreateWindow(int width, int height, const char* title);
    void DestroyWindow(Window* window);

    void PollEvents();
    bool WindowShouldClose(Window* window);

    double GetTimeSeconds();
    double GetDeltaTime();

    bool IsKeyDown(int key);
}

