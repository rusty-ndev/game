#include "platform.h"
#include "input.h"
#include "Renderer/shader.h"
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main() {
    if (!Platform::Init()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    auto* window = Platform::CreateWindow(1280, 720, "My Game");
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

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
void main() {
    gl_Position = vec4(aPos, 1.0);
}
)";

const std::string fragmentShader = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(0.8, 0.3, 0.2, 1.0);
}
)";

Shader shader(vertexShader, fragmentShader);


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

    shader.Bind();
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


