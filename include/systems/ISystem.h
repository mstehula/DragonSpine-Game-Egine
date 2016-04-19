#ifndef SYSTEM_H
#define SYSTEM_H

#include "engine\EngineObject.h"
#include "messages/GameMessage.h"

namespace systems
{
    class ObjectSystem;

    class ISystem
    {
    public:
        virtual void Init() = 0;
        virtual void Update(float dt, ObjectSystem& factory) = 0;
        virtual void SendMessageSync(messages::GameMessage* msg) = 0;
        virtual void SendMessageAsync(messages::GameMessage* msg) = 0;
        void SendMessage(messages::GameMessage* msg) { SendMessageSync(msg); }
        virtual ~ISystem(){}
    };

}

#endif // SYSTEM_H
