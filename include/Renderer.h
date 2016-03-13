#ifndef RENDERER_H
#define RENDERER_H

#include <GLFW/glfw3.h>

namespace DragonSpineGameEngine {

    class Renderer
    {
        public:
            Renderer();
            virtual ~Renderer();

            void testWindow();
            void openWindow();
            void closeWindow();
        protected:

        private:
            GLFWwindow* window;
    };

}

#endif // RENDERER_H
