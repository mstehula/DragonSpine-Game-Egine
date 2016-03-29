#ifndef RENDERER_H
#define RENDERER_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <GLFW/glfw3.h>

namespace dragonspinegameengine {

    class Renderer
    {
        public:
            void TestWindow();
            void InitWindow();

            void Render();
            void ClearWindow();
        private:
            GLFWwindow* window_;
    };

    class Camera
    {
        public:
            Camera();

            static Camera* GetCamera();

            void SetPosition(glm::vec3 r);
            void SetRotation(glm::vec3 r);

            void CalculateViewMatrix();
            glm::mat4x4 GetViewMatrix();
        private:
            glm::vec3 camera_pos_ = glm::vec3(0.0f, 0.0f, 0.0f);
            glm::vec3 camera_front_ = glm::vec3(0.0f, 0.0f, -1.0f);
            glm::vec3 camera_up_ = glm::vec3(0.0f, 1.0f, 0.0f);

            glm::mat4x4 translation_matrix_;
            glm::mat4x4 rotation_matrix_;
            glm::mat4x4 view_matrix_;
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
            glm::vec4 pos_;
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

    class RenderableObject
    {
        public:
            RenderableObject();
            RenderableObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);

            void SetPosition(glm::vec3 pos);
            void SetRotation(glm::vec3 rot);
            void SetScale(glm::vec3 scale);

            glm::mat4x4 GetModelMatrix();
            void CalculateModelMatrix();

            void Render();

            Mesh* GetMesh();
        private:
            Mesh* mesh_;

            glm::mat4x4 translation_matrix_;
            glm::mat4x4 rotation_matrix_;
            glm::mat4x4 scale_matrix_;
            glm::mat4x4 model_matrix_;
    };
}

#endif // RENDERER_H
