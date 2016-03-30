#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

namespace dragonspinegameengine
{

    class Input
    {
        public:
            static Input* GetInstance();

            void Update();

            void CursorPosCallbackImpl(GLFWwindow* window, double cursor_x, double cursor_y);
            static void CursorPosCallback(GLFWwindow* window, double cursor_x, double cursor_y)
            {
                GetInstance()->CursorPosCallbackImpl(window, cursor_x, cursor_y);
            }

            void CursorButtonCallbackImpl(GLFWwindow* window, int button, int action, int mods);
            static void CursorButtonCallback(GLFWwindow* window, int button, int action, int mods)
            {
                GetInstance()->CursorButtonCallbackImpl(window, button, action, mods);
            }

            void KeyCallbackImpl(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                GetInstance()->KeyCallbackImpl(window, key, scancode, action, mods);
            }
        protected:

        private:
            static Input* instance_;

            double cursor_prev_x_;
            double cursor_prev_y_;
            double cursor_d_x_;
            double cursor_d_y_;

            bool is_cursor_bound = 0;

            Input();
    };

}


#endif // INPUT_H
