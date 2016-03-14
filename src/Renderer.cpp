#include <stdlib.h>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Engine.h"

namespace dragonspinegameengine {

    void Renderer::TestWindow()
    {
        debug(kDebugAll, "Renderer - Test window");
        window_ = glfwCreateWindow(640, 480, "Simple Example", NULL, NULL);

        if(!window_)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window_);
        glfwSwapInterval(1);

        while(!glfwWindowShouldClose(window_))
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

            glfwSwapBuffers(window_);
            glfwPollEvents();
        }

        glfwDestroyWindow(window_);
    }

    void Renderer::OpenWindow()
    {
        window_ = glfwCreateWindow(640, 480, "Simple Example", NULL, NULL);

        if(!window_)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window_);
        glfwSwapInterval(1);

        printf("%s\n", glGetString(GL_VERSION));
    }

    void Renderer::CloseWindow()
    {
        glfwDestroyWindow(window_);
    }

    void Renderer::Render()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window_);
    }

}
