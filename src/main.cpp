#include "platform.h"
#include "input.h"
#include "Renderer/shader.h"
#include "Renderer/camera.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct MouseState {
    double x;
    double y;
};

namespace Input {
    MouseState mouse;

    void PollEvents(GLFWwindow* window); // updates mouse.x and mouse.y
    MouseState GetMouseState() { return mouse; }
}

void Input::PollEvents(GLFWwindow* window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    mouse.x = xpos;
    mouse.y = ypos;
}


int main() {
    if (!Platform::Init()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    auto* window = Platform::CreateWindow(1920, 1080, "My Game");
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }
    glfwSetInputMode((GLFWwindow*)window->handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
     0.0f,  0.5f, 0.0f, // top
    -0.5f, -0.5f, 0.0f, // bottom left
     0.5f, -0.5f, 0.0f  // bottom right
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    const std::string vertexShader = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;

    uniform mat4 uModel;
    uniform mat4 uView;
    uniform mat4 uProjection;

    void main() {
        gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
    })";

    const std::string fragmentShader = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(0.8, 0.3, 0.2, 1.0);
    }
    )";

    Shader shader(vertexShader, fragmentShader);

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

    glm::mat4 projection = glm::perspective(
    glm::radians(camera.Fov),
    1280.0f / 720.0f,
    0.1f,
    100.0f
    );

    float lastX = 1280.0f / 2.0f;
    float lastY = 720.0f / 2.0f;
    bool firstMouse = true;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    
    Input::PollEvents((GLFWwindow*)window->handle);

    if (!window) {
        std::cerr << "Failed to create window\n";
        Platform::Shutdown();
        return -1;
    }

    Input::Init();

    while (!Platform::WindowShouldClose(window)) {
    Platform::PollEvents();
    Input::PollEvents();

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Keyboard movement
    if (Input::IsKeyPressed(Input::KeyCode::W))
        camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (Input::IsKeyPressed(Input::KeyCode::S))
        camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
    if (Input::IsKeyPressed(Input::KeyCode::A))
        camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
    if (Input::IsKeyPressed(Input::KeyCode::D))
        camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);

    // Mouse movement
    auto mouse = Input::GetMouseState();
    if (firstMouse) {
        lastX = mouse.x;
        lastY = mouse.y;
        firstMouse = false;
    }
    float xoffset = mouse.x - lastX;
    float yoffset = lastY - mouse.y;
    lastX = mouse.x;
    lastY = mouse.y;
    camera.ProcessMouseMovement(xoffset, yoffset);

    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Upload matrices
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.GetViewMatrix();

    shader.Bind();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "uModel"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "uView"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "uProjection"), 1, GL_FALSE, &projection[0][0]);

    // Draw triangle
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    shader.Unbind();

    glfwSwapBuffers((GLFWwindow*)window->handle);
    }


    Input::Shutdown();
    Platform::DestroyWindow(window);
    Platform::Shutdown();
    return 0;
}


