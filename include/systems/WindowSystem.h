#ifndef WINDOW_SYSTEM_H
#define WINDOW_SYSTEM_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "engine/Engine.h"
#include "systems/ISystem.h"
#include "systems/messages/GameMessage.h"

namespace systems
{
    class WindowSystem : public ISystem
    {
    public:
        void Init();
        void Update(float dt, ObjectSystem& factory);
        void SendMessageSync(messages::GameMessage* msg);
        void SendMessageAsync(messages::GameMessage* msg);
        ~WindowSystem(){}
    private:
        GLFWwindow* window_;
    };

}
#endif // WINDOW_SYSTEM_H
