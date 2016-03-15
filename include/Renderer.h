#ifndef RENDERER_H
#define RENDERER_H

#include <GLFW/glfw3.h>

namespace dragonspinegameengine {

    class Renderer
    {
        public:
            void TestWindow();
            void OpenWindow();
            void CloseWindow();

            void Render();
        private:
            GLFWwindow* window_;
    };

    class Vector2f
    {
        public:
            Vector2f(float x1, float x2);

            float Length();
            float Dot(Vector2f r);
            Vector2f Normalize();

            Vector2f Add(Vector2f r);
            Vector2f Add(float x1, float x2);
            Vector2f Sub(Vector2f r);
            Vector2f Sub(float x1, float x2);
            Vector2f Mul(Vector2f r);
            Vector2f Mul(float x1, float x2);
            Vector2f Div(Vector2f r);
            Vector2f Div(float x1, float x2);

            float GetX1();
            void SetX1(float x1);
            float GetX2();
            void SetX2(float x2);

            const char* ToString();

        private:
            float x1_;
            float x2_;
    };

    class Vector3f
    {
        public:
            Vector3f(float x1, float x2, float x3);

            float Length();
            float Dot(Vector3f r);
            Vector3f Cross(Vector3f r);
            Vector3f Normalize();

            Vector3f Add(Vector3f r);
            Vector3f Add(float x1, float x2, float x3);
            Vector3f Sub(Vector3f r);
            Vector3f Sub(float x1, float x2, float x3);
            Vector3f Mul(Vector3f r);
            Vector3f Mul(float x1, float x2, float x3);
            Vector3f Div(Vector3f r);
            Vector3f Div(float x1, float x2, float x3);

            float GetX1();
            void SetX1(float x1);
            float GetX2();
            void SetX2(float x2);
            float GetX3();
            void SetX3(float x3);

            const char* ToString();
        private:
            float x1_;
            float x2_;
            float x3_;
    };

    class Matrix4f
    {
        public:
            Matrix4f();

            Matrix4f InitIdentiy();
        private:
            float m_[4][4];
    };

    class Quaternion
    {

    };

    class Vertex
    {
        public:
            Vertex(Vector3f pos);

            Vector3f GetPos();
            void SetPos(Vector3f r);

            int vertex_size_ = 3;
        private:
            Vector3f pos_;
    };

    class Mesh
    {
        public:
            Mesh();

            void AddVertices(Vertex* vertices, int vertices_size, int* indices, int indices_size);
            void Draw();
        private:
            int vertices_buffer_object_;
            int indices_buffer_object_;
            int size_;
    };
}

#endif // RENDERER_H
