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
        position_ += velocity_;
    }

    void PhysicsObject::SetPosition(glm::vec3 position)
    {
        position_ = position;
    }

    glm::vec3 PhysicsObject::GetPosition()
    {
        return position_;
    }

    void PhysicsObject::SetVelocity(glm::vec3 velocity)
    {
        velocity_ = velocity;
    }

    glm::vec3 PhysicsObject::GetVelocity()
    {
        return velocity_;
    }

    void PhysicsObject::ApplyForce(float x_force, float y_force, float z_force)
    {
        glm::vec3 acceleration = glm::vec3(x_force * mass_, y_force * mass_, z_force * mass_);
        velocity_ += acceleration;
    }

}

