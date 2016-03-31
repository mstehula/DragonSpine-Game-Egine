#include "PhysicsEngine.h"

namespace dragonspinegameengine
{
    PhysicsEngine* PhysicsEngine::instance_;
    PhysicsEngine* PhysicsEngine::GetInstance()
    {
        if(instance_ == nullptr)
        {
            instance_ = new PhysicsEngine();
        }
        return instance_;
    }

    PhysicsEngine::PhysicsEngine()
    {
        //ctor
    }

    void PhysicsEngine::Simulate(PhysicsObject* physics_object)
    {
        physics_object->Simulate();
    }

    void PhysicsObject::Simulate()
    {
        position_ = position_ + velocity_;
    }

    void PhysicsObject::ApplyForce(float x_force, float y_force, float z_force)
    {

    }

    void PhysicsObject::ApplyForceDir(float front_force, float side_force, float up_force)
    {

    }

}

