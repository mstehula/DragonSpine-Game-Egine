#ifndef RENDERER_H
#define RENDERER_H

#include <GLFW/glfw3.h>

namespace dragonspinegameengine {

    class Renderer
    {
        public:
            void testWindow();
            void openWindow();
            void closeWindow();

            void render();
        private:
            GLFWwindow* window;
    };
}

#endif // RENDERER_H
