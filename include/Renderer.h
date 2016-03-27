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
        private:
            GLFWwindow* window_;
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
            void AddVertices(GLfloat* vertex_buffer_data, int vertex_buffer_data_size);
            void Draw();
        private:
            GLuint vertex_buffer_;
            int vertex_buffer_size_;
            GLuint indices_buffer_object_;
            int size_;
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
