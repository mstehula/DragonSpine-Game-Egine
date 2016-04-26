
#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <systems/ISystem.h>

#include "systems/messages/GameMessage.h"

namespace systems
{

    class PhysicsSystem : public ISystem
    {
    public:
        void Init();
        void Update(float dt, ObjectSystem& factory);
        void SendMessageSync(messages::GameMessage* msg);
        void SendMessageAsync(messages::GameMessage* msg);
    };
}

#endif //PHYSICSSYSTEM_H
