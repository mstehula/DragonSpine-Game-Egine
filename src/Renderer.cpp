#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Engine.h"

using namespace glm;

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

    void Renderer::InitWindow()
    {
        if(!glfwInit())
        {
            fprintf(stderr, "Error initializing glfw");
            exit(EXIT_FAILURE);
        }

        glfwWindowHint(GLFW_SAMPLES, 16); // 4x antialiasing
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

        // Open a window and create its OpenGL context
        window_ = glfwCreateWindow( 1024, 768, "DragonSpine Game Engine Internal Testing Window", NULL, NULL);
        if(window_ == NULL){
            debug(3, "Failed to create window");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(window_); // Initialize GLEW
        glewExperimental=true; // Needed in core profile
        if(glewInit() != GLEW_OK) {
            fprintf(stderr, "Failed to initialize GLEW\n");
            exit(EXIT_FAILURE);
        }

        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        glfwSetInputMode(window_, GLFW_STICKY_KEYS, GL_TRUE);
    }

    void Renderer::Render()
    {
        if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window_) == GL_TRUE)
                Engine::GetInstance()->stop();

        glfwSwapBuffers(window_);
    }

    Vertex::Vertex(vec3 pos)
    {
        pos_ = vec4(pos.x, pos.y, pos.z, 1.0f);
    }

    Vertex::~Vertex()
    {
    }

    vec4 Vertex::GetPos()
    {
        return pos_;
    }

    void Vertex::SetPos(vec3 pos)
    {
        pos_ = vec4(pos.x, pos.y, pos.z, 1.0f);
    }

    Mesh::Mesh()
    {

    }

    void Mesh::AddVertices()
    {
        const GLfloat vertex_buffer_data[] =
        {
            -0.8f, -0.4f, 0.0f,
            0.8f, -0.4f, 0.0f,
            0.0f, 0.4f, 0.0f
        };

        glGenBuffers(1, &vertex_buffer_);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
    }

    void Mesh::Draw()
    {
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            0
        );
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(0);
    }

}
