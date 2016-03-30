#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <GLM/mat4x4.hpp>
#include <glm/gtx/transform.hpp>

#include "Input.h"
#include "Engine.h"
#include "Renderer.h"

namespace dragonspinegameengine {

    Renderer::Renderer()
    {
        player_camera_ = new Camera();
        aux_camera_ = new Camera();
    }

    Renderer::~Renderer()
    {
        delete player_camera_;
        delete aux_camera_;
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
        window_ = glfwCreateWindow( window_width_, window_height_, "DragonSpine Game Engine Internal Testing Window", NULL, NULL);
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
        glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window_, Input::CursorPosCallback);
        glfwSetMouseButtonCallback(window_, Input::CursorButtonCallback);
        glfwSetKeyCallback(window_, Input::KeyCallback);
        glClearColor(.2f, .2f, .2f, 1.0f);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    void Renderer::SetCamera(CameraType camera)
    {
        if(camera == CameraType::Player)
        {
            current_camera_ = player_camera_;
        }
        else if(camera == CameraType::Aux)
        {
            current_camera_ = aux_camera_;
        }
    }

    Camera* Renderer::GetCamera()
    {
        return current_camera_;
    }

    void Renderer::Render()
    {
        if(glfwWindowShouldClose(window_) == GL_TRUE)
                Engine::GetInstance()->stop();

        glfwSwapBuffers(window_);
    }

    void Renderer::Input()
    {
        Input::GetInstance()->Update();
        if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            Engine::GetInstance()->stop();
        }
    }

    glm::mat4x4 Renderer::GetPerspectiveMatrix()
    {
        return glm::perspective(glm::radians(20.0f), (float) (window_width_ / window_height_), 0.1f, 100.0f);
    }

    void Renderer::ClearWindow()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    Camera::Camera()
    {
        CalculateViewMatrix();
    }

    void Camera::SetPitch(float pitch)
    {
        pitch_ = pitch;
        CalculateViewDirection();
        CalculateViewMatrix();
    }

    void Camera::SetYaw(float yaw)
    {
        yaw_ = yaw;
        CalculateViewDirection();
        CalculateViewMatrix();
    }

    void Camera::SetRoll(float roll)
    {
        roll_ = roll;
        CalculateViewDirection();
        CalculateViewMatrix();
    }

    void Camera::SetRotation(float pitch, float yaw, float roll)
    {
        pitch_ = pitch;
        yaw_ = yaw;
        roll_ = roll;
        CalculateViewDirection();
        CalculateViewMatrix();
    }

    void Camera::SetPosition(float x, float y, float z)
    {
        camera_pos_ = glm::vec3(x, y, z);
        CalculateViewMatrix();
    }

    void Camera::Rotate(float d_pitch, float d_yaw, float d_roll)
    {
        pitch_ += d_pitch;
        yaw_ += d_yaw;

        CalculateViewDirection();
        CalculateViewMatrix();
    }

    void Camera::Move(float d_x, float d_y, float d_z)
    {
        camera_pos_ = camera_pos_ + glm::vec3(d_x, d_y, d_z);
        CalculateViewMatrix();
    }

    void Camera::CalculateViewDirection()
    {
        camera_front_ = glm::vec3(
            glm::sin(yaw_) * glm::cos(pitch_),
            glm::sin(pitch_),
            -glm::cos(yaw_) * glm::cos(pitch_)
        );

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
