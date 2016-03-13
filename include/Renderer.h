#ifndef RENDERER_H
#define RENDERER_H

#include <GLFW/glfw3.h>


class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();

        void testWindow();
        void openWindow();
    protected:

    private:
        GLFWwindow* window;
};

#endif // RENDERER_H
