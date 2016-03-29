#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <GLM/mat4x4.hpp>
#include <glm/gtx/transform.hpp>

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
        glClearColor(.2f, .2f, .2f, 1.0f);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    void Renderer::Render()
    {
        if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window_) == GL_TRUE)
                Engine::GetInstance()->stop();

        glfwSwapBuffers(window_);
    }

    void Renderer::ClearWindow()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    Camera::Camera()
    {
        CalculateViewMatrix();
    }

    void Camera::SetPosition(glm::vec3 r)
    {
        camera_pos_ = r;
        CalculateViewMatrix();
    }

    void Camera::SetRotation(glm::vec3 r)
    {
        glm::mat4x4 rx = glm::rotate(r.x, glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4x4 ry = glm::rotate(r.y, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4x4 rz = glm::rotate(r.z, glm::vec3(0.0f, 0.0f, 1.0f));

        rotation_matrix_ = rz * ry * rx;
    }

    void Camera::CalculateViewMatrix()
    {
        view_matrix_ = glm::lookAt(camera_pos_, camera_pos_ + camera_front_, camera_up_);
    }

    glm::mat4x4 Camera::GetViewMatrix()
    {
        return view_matrix_;
    }

    Vertex::Vertex(glm::vec3 pos)
    {
        pos_ = glm::vec4(pos.x, pos.y, pos.z, 1.0f);
    }

    Vertex::~Vertex()
    {
    }

    glm::vec4 Vertex::GetPos()
    {
        return pos_;
    }

    void Vertex::SetPos(glm::vec3 pos)
    {
        pos_ = glm::vec4(pos.x, pos.y, pos.z, 1.0f);
    }

    void Mesh::AddVertices(GLfloat* vertex_buffer_data, int vertex_buffer_data_size, int* index_buffer_data, int index_buffer_data_size)
    {
        vertex_buffer_size_ = vertex_buffer_data_size;
        index_buffer_size_ = index_buffer_data_size;

        glGenBuffers(1, &vertex_buffer_);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
        glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data_size, vertex_buffer_data, GL_STATIC_DRAW);

        glGenBuffers(1, &index_buffer_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data_size, index_buffer_data, GL_STATIC_DRAW);
    }

    void Mesh::Draw()
    {
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
        glDrawElements(GL_TRIANGLES, index_buffer_size_, GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(0);
    }

    RenderableObject::RenderableObject()
    {
        translation_matrix_ = glm::mat4x4(1.0f);
        rotation_matrix_ = glm::mat4x4(1.0f);
        scale_matrix_ = glm::mat4x4(1.0f);
        mesh_ = new Mesh();
    }

    RenderableObject::RenderableObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
    {
        mesh_ = new Mesh();
        SetPosition(pos);
        SetRotation(rot);
        SetScale(scale);
    }

    void RenderableObject::SetPosition(glm::vec3 pos)
    {
        translation_matrix_ = glm::translate(pos);
        CalculateModelMatrix();
    }

    void RenderableObject::SetRotation(glm::vec3 rot)
    {
        glm::mat4x4 rx = glm::rotate(rot.x, glm::vec3(1.0,0.0,0.0));
        glm::mat4x4 ry = glm::rotate(rot.y, glm::vec3(0.0,1.0,0.0));
        glm::mat4x4 rz = glm::rotate(rot.z, glm::vec3(0.0,0.0,1.0));

        rotation_matrix_ = rz * ry * rx;
        CalculateModelMatrix();
    }

    void RenderableObject::SetScale(glm::vec3 scale)
    {
        scale_matrix_ = glm::scale(scale);
        CalculateModelMatrix();
    }

    glm::mat4x4 RenderableObject::GetModelMatrix()
    {
        return model_matrix_;
    }

    void RenderableObject::CalculateModelMatrix()
    {
        model_matrix_ = translation_matrix_ * rotation_matrix_ * scale_matrix_;
    }

    Mesh* RenderableObject::GetMesh()
    {
        return mesh_;
    }

    void RenderableObject::Render()
    {
        Engine::GetBasicShader()->SetModelMatrix(GetModelMatrix());
        GetMesh()->Draw();
    }
}
