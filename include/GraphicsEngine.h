#ifndef RENDERER_H
#define RENDERER_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <GLFW/glfw3.h>

#include "Shaders.h"

namespace dragonspinegameengine {

    class Camera;
    class GraphicsObject;

    class GraphicsEngine
    {
    public:
        GraphicsEngine();
        virtual ~GraphicsEngine();

        enum CameraType {Player, Aux};
        void SetCamera(CameraType camera);
        Camera* GetCamera();

        void CreateContext();
        void ShowWindow(bool show);
        void SetWindowSize(int window_width, int window_height);
        void CheckCloseState();

        void SetupShaders();

        void RegisterObject(GraphicsObject* object);
        void UnregisterObject(GraphicsObject* object);

        void PreRender();
        void Render();
        void PostRender();

        void ClearWindow();
    private:
        GLFWwindow* window_;

        Camera* current_camera_;

        Camera* aux_camera_;
        Camera* player_camera_;

        Shader* shader_;

        int window_width_ = 1024;
        int window_height_ = 768;
    };

    class Camera
    {
    public:
        Camera();

        void SetPitch(float pitch);
        void SetYaw(float yaw);
        void SetRoll(float roll);
        void SetRotation(float pitch, float yaw, float roll);
        void SetPosition(float x, float y, float z);

        void Rotate(float d_pitch, float d_yaw, float d_roll);
        void Move(float d_x, float d_y, float d_z);

        glm::mat4x4 GetViewMatrix();
        void SetFOV();
        glm::mat4x4 GetPerspectiveMatrix();
    private:
        const glm::vec3 camera_pox_x_ = glm::vec3(0.0f, 0.0f, -1.0f);

        float pitch_;
        float yaw_;
        float roll_;

        glm::vec3 camera_pos_ = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 camera_front_ = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 camera_up_ = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::mat4x4 view_matrix_;

        void CalculateViewDirection();
        void CalculateViewMatrix();
    };

    class Vertex
    {
    public:
        Vertex(glm::vec3 pos);
        virtual ~Vertex();

        glm::vec4 GetPos();
        void SetPos(glm::vec3 r);
        static const int kSize = 3;
    private:
        glm::vec4 position_;
    };

    class Mesh
    {
    public:
        void AddVertices(GLfloat* vertex_buffer_data, int vertex_buffer_data_size, int* index_buffer_data, int index_buffer_data_size);
        void Draw();
    private:
        GLuint vertex_buffer_;
        GLuint index_buffer_;

        int vertex_buffer_size_;
        int index_buffer_size_;
    };

    class GraphicsObject : public virtual EngineObject
    {
    public:
        GraphicsObject();
        virtual ~GraphicsObject();

        void SetPosition(glm::vec3 pos);
        glm::vec3 GetPosition();
        void SetRotation(glm::vec3 rot);
        void SetScale(glm::vec3 scale);

        glm::mat4x4 GetModelMatrix();
        void CalculateModelMatrix();

        void Render();

        Mesh* GetMesh();
    private:
        Mesh* mesh_;

        glm::vec3 position_;

        glm::mat4x4 translation_matrix_;
        glm::mat4x4 rotation_matrix_;
        glm::mat4x4 scale_matrix_;
        glm::mat4x4 model_matrix_;
    };
}

#endif // RENDERER_H
