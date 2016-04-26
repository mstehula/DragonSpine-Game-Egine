
#include "systems/ObjectSystem.h"
#include "systems/PhysicsSystem.hpp"
#include "systems/components/Components.h"

namespace systems
{
    void PhysicsSystem::Init()
    {

    }

    void PhysicsSystem::Update(float dt, ObjectSystem& factory)
    {
        EngineArray& objects = factory.GetObjects();
        PositionArray& positions = factory.GetPositions();
        MotionArray& motion = factory.GetMotion();

        for(unsigned int i = 0; i < objects.Size(); i++)
        {
            motion[i].linear_velocity += motion[i].linear_acceleration * dt;
            motion[i].rotational_velocity += motion[i].rotational_acceleration * dt;

            positions[i].position += motion[i].linear_velocity * dt;
            positions[i].rotation += motion[i].rotational_velocity * dt;
        }
    }

    void PhysicsSystem::SendMessageSync(messages::GameMessage* msg)
    {

    }

    void PhysicsSystem::SendMessageAsync(messages::GameMessage* msg)
    {

    }
}
