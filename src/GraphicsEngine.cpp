#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <GLM/mat4x4.hpp>
#include <glm/gtx/transform.hpp>

#include "engine\Engine.h"
#include "GraphicsEngine.h"
#include "InputEngine.h"
#include "Shaders.h"

namespace systems {

    GraphicsEngine::GraphicsEngine()
    {
        player_camera_ = new Camera();
        aux_camera_ = new Camera();
    }

    GraphicsEngine::~GraphicsEngine()
    {
        delete player_camera_;
        delete aux_camera_;
    }

    void GraphicsEngine::SetCamera(CameraType camera)
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

    Camera* GraphicsEngine::GetCamera()
    {
        return current_camera_;
    }

    void GraphicsEngine::CreateContext()
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
        glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

        window_ = glfwCreateWindow(100, 100, "Testing - should be invisible", NULL, NULL);
        if(window_ == NULL){
            engine::debug(3, "Failed to create window");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window_);
        glewExperimental=true; // Needed in core profile
        if(glewInit() != GLEW_OK) {
            fprintf(stderr, "Failed to initialize GLEW\n");
            exit(EXIT_FAILURE);
        }

        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        glClearColor(.2f, .2f, .2f, 1.0f);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    void GraphicsEngine::ShowWindow(bool show)
    {
        if(show)
        {
            glfwShowWindow(window_);
        }
        else
        {
            glfwHideWindow(window_);
        }
    }

    void GraphicsEngine::SetWindowSize(int window_width, int window_height)
    {
        window_width_ = window_width;
        window_height_ = window_height;

        glfwSetWindowSize(window_, window_width_, window_height_);
    }

    void GraphicsEngine::CheckCloseState()
    {
        if(glfwWindowShouldClose(window_) == GL_TRUE)
        {

        }
    }

    void GraphicsEngine::SetupShaders()
    {

    }

    void GraphicsEngine::RegisterObject(GraphicsObject* object)
    {

    }

    void GraphicsEngine::UnregisterObject(GraphicsObject* object)
    {

    }

    void GraphicsEngine::PreRender()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GraphicsEngine::Render()
    {

    }

    void GraphicsEngine::PostRender()
    {
        glfwSwapBuffers(window_);
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

    glm::mat4x4 Camera::GetPerspectiveMatrix()
    {
        return glm::perspective(glm::radians(20.0f), (float) (1000 / 800), 0.1f, 100.0f);
    }

    Vertex::Vertex(glm::vec3 pos)
    {
        position_ = glm::vec4(pos.x, pos.y, pos.z, 1.0f);
    }

    Vertex::~Vertex()
    {
    }

    glm::vec4 Vertex::GetPos()
    {
        return position_;
    }

    void Vertex::SetPos(glm::vec3 pos)
    {
        position_ = glm::vec4(pos.x, pos.y, pos.z, 1.0f);
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

    GraphicsObject::GraphicsObject()
    {

        mesh_ = new Mesh();

        translation_matrix_ = glm::mat4x4(1.0f);
        rotation_matrix_ = glm::mat4x4(1.0f);
        scale_matrix_ = glm::mat4x4(1.0f);
    }

    GraphicsObject::~GraphicsObject()
    {

    }

    void GraphicsObject::SetPosition(glm::vec3 pos)
    {
        translation_matrix_ = glm::translate(pos);
        CalculateModelMatrix();
    }

    glm::vec3 GraphicsObject::GetPosition()
    {
        return position_;
    }

    void GraphicsObject::SetRotation(glm::vec3 rot)
    {
        glm::mat4x4 rx = glm::rotate(rot.x, glm::vec3(1.0,0.0,0.0));
        glm::mat4x4 ry = glm::rotate(rot.y, glm::vec3(0.0,1.0,0.0));
        glm::mat4x4 rz = glm::rotate(rot.z, glm::vec3(0.0,0.0,1.0));

        rotation_matrix_ = rz * ry * rx;
        CalculateModelMatrix();
    }

    void GraphicsObject::SetScale(glm::vec3 scale)
    {
        scale_matrix_ = glm::scale(scale);
        CalculateModelMatrix();
    }

    glm::mat4x4 GraphicsObject::GetModelMatrix()
    {
        return model_matrix_;
    }

    void GraphicsObject::CalculateModelMatrix()
    {
        model_matrix_ = translation_matrix_ * rotation_matrix_ * scale_matrix_;
    }

    Mesh* GraphicsObject::GetMesh()
    {
        return mesh_;
    }

    void GraphicsObject::Render()
    {
        GetMesh()->Draw();
    }
}
