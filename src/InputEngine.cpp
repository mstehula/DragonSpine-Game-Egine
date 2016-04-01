#include "Engine.h"
#include "InputEngine.h"

namespace dragonspinegameengine
{
    InputEngine* InputEngine::instance_ = 0;

    InputEngine* InputEngine::GetInstance()
    {
        if(InputEngine::instance_ == nullptr)
        {
            InputEngine::instance_ = new InputEngine();
        }
        return InputEngine::instance_;
    }

    void InputEngine::PollInput()
    {
        glfwPollEvents();
    }

    void InputEngine::CursorPosCallbackImpl(GLFWwindow* window, double cursor_x, double cursor_y)
    {
        float sensitivity = .005f;

        cursor_d_x_ = cursor_x - cursor_prev_x_;
        cursor_d_y_ = cursor_y - cursor_prev_y_;

        cursor_prev_x_ = cursor_x;
        cursor_prev_y_ = cursor_y;
    }

    void InputEngine::CursorButtonCallbackImpl(GLFWwindow* window, int button, int action, int mods)
    {

    }

    void InputEngine::KeyCallbackImpl(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        float sensitivity = .5f;

        debug(kDebugAll, "This is a buttonpress");

        // Move forward
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            debug(kDebugAll, "Move Forward");
        }
        // Move backward
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        }
        // Strafe right
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        }
        // Strafe left
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        }

    }

    InputEngine::InputEngine()
    {
        int width, height;
        glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
        glfwSetCursorPos(glfwGetCurrentContext(), width/2, height/2);
    }

}
