#ifndef RENDERER_H
#define RENDERER_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <GLFW/glfw3.h>
using namespace glm;

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
            Vertex(vec3 pos);
            virtual ~Vertex();

            vec4 GetPos();
            void SetPos(vec3 r);
            static const int kSize = 3;
        private:
            vec4 pos_;
    };

    class Mesh
    {
        public:
            Mesh();

            void AddVertices();
            void Draw();
        private:
            GLuint vertex_buffer_;
            GLuint indices_buffer_object_;
            int size_;
    };
}

#endif // RENDERER_H
