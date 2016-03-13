#include <stdlib.h>
#include <stdio.h>

#include "Renderer.h"
#include "Debug.h"

namespace DragonSpineGameEngine {

    Renderer::Renderer()
    {
        if(!glfwInit())
        {
            error("Cannot init glfw, exiting\n");
            exit(EXIT_FAILURE);
        }
    }

    Renderer::~Renderer()
    {
        glfwTerminate();
    }

    void Renderer::testWindow()
    {
        window = glfwCreateWindow(640, 480, "Simple Example", NULL, NULL);

        if(!window)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        while(!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-(640/480.0), (640/480.0), -1.0f, 1.0f, 1.0f, -1.0f);

            glMatrixMode(GL_MODELVIEW);

            glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(-0.6f, -0.4f, 0.0f);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.6f, -0.4f, 0.0f);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 0.6f, 0.0f);
            glEnd();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
    }

    void Renderer::openWindow()
    {
        window = glfwCreateWindow(640, 480, "Simple Example", NULL, NULL);

        if(!window)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
    }

    void Renderer::closeWindow()
    {
        glfwDestroyWindow(window);
    }

    void Renderer::render()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}
