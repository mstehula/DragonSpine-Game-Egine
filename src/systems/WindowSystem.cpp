
#include <stdlib.h>

#include "engine/Engine.h"
#include "systems/WindowSystem.h"

namespace systems
{
    void WindowSystem::Init()
    {
        if(!glfwInit())
        {
            exit(EXIT_FAILURE);
        }

        glfwWindowHint(GLFW_SAMPLES, 16); // 4x antialiasing
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
        glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

        GLFWwindow* window_ = glfwCreateWindow(800, 600, "Testing - DragonSpine Game Engine", NULL, NULL);
        if(window_ == NULL){
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window_);
        glewExperimental=true; // Needed in core profile
        if(glewInit() != GLEW_OK) {
            exit(EXIT_FAILURE);
        }

        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        glClearColor(.2f, .2f, .2f, 1.0f);
    }

    void WindowSystem::Update(float dt, ObjectSystem& factory)
    {
        glfwPollEvents();

        if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwHideWindow(glfwGetCurrentContext());
        }
    }

    void WindowSystem::SendMessageSync(messages::GameMessage* msg)
    {

    }

    void WindowSystem::SendMessageAsync(messages::GameMessage* msg)
    {

    }
}
