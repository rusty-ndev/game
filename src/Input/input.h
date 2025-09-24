#pragma once

namespace Input {

    enum class KeyCode {
        Unknown = -1,
        Escape  = 256, // maps to GLFW_KEY_ESCAPE
        W = 87,
        A = 65,
        S = 83,
        D = 68,
        // ... add more as needed
    };

    void Init();
    void Shutdown();

    bool IsKeyPressed(KeyCode key);
    bool IsKeyReleased(KeyCode key);
    bool IsKeyDown(KeyCode key);   // held
    bool IsKeyUp(KeyCode key);     // not pressed

    void PollEvents(); // update input state each frame
}

