#include "Engine.h"
#include "Input.h"

namespace dragonspinegameengine
{
    Input* Input::instance_ = 0;

    Input* Input::GetInstance()
    {
        if(Input::instance_ == nullptr)
        {
            Input::instance_ = new Input();
        }
        return Input::instance_;
    }

    void Input::Update()
    {
        glfwPollEvents();
    }

    void Input::CursorPosCallbackImpl(GLFWwindow* window, double cursor_x, double cursor_y)
    {
        float sensitivity = .005f;

        cursor_d_x_ = cursor_x - cursor_prev_x_;
        cursor_d_y_ = cursor_y - cursor_prev_y_;

        cursor_prev_x_ = cursor_x;
        cursor_prev_y_ = cursor_y;

        Engine::GetRenderer()->GetCamera()->Rotate(cursor_d_y_ * sensitivity, cursor_d_x_ * sensitivity, 0);
    }

    void Input::CursorButtonCallbackImpl(GLFWwindow* window, int button, int action, int mods)
    {

    }

    void Input::KeyCallbackImpl(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        float sensitivity = .5f;

        debug(kDebugAll, "This is a buttonpress");

        // Move forward
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            Engine::GetRenderer()->GetCamera()->Move(-1.0f * sensitivity, 0.0f, 0.0f);

            debug(kDebugAll, "Move Forward");
        }
        // Move backward
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            Engine::GetRenderer()->GetCamera()->Move(1.0f * sensitivity, 0.0f, 0.0f);
        }
        // Strafe right
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            Engine::GetRenderer()->GetCamera()->Move(0.0f, 0.0f, -1.0f * sensitivity);
        }
        // Strafe left
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            Engine::GetRenderer()->GetCamera()->Move(0.0f, 0.0f, 1.0f * sensitivity);
        }

    }

    Input::Input()
    {
        int width, height;
        glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
        glfwSetCursorPos(glfwGetCurrentContext(), width/2, height/2);
    }

}
