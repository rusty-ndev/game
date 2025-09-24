#include "input.h"
#include <GLFW/glfw3.h>

// We rely on GLFW's "current context" to know the active window.
// (later you can make this explicit if you support multiple windows)

namespace Input {

    void Init() {
        // nothing yet
    }

    void Shutdown() {
        // nothing yet
    }

    void PollEvents() {
        glfwPollEvents();
    }

    bool IsKeyPressed(KeyCode key) {
        auto* window = glfwGetCurrentContext();
        int state = glfwGetKey(window, static_cast<int>(key));
        return state == GLFW_PRESS;
    }

    bool IsKeyReleased(KeyCode key) {
        auto* window = glfwGetCurrentContext();
        int state = glfwGetKey(window, static_cast<int>(key));
        return state == GLFW_RELEASE;
    }

    bool IsKeyDown(KeyCode key) {
        return IsKeyPressed(key);
    }

    bool IsKeyUp(KeyCode key) {
        return IsKeyReleased(key);
    }

}

