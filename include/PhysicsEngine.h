#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <glm/vec3.hpp>

namespace dragonspinegameengine
{
    class PhysicsObject;

    class PhysicsEngine
    {
        public:
            PhysicsEngine();

            void RegisterObject(PhysicsObject* object){};
            void UnregisterObject(PhysicsObject* object){};

            void Simulate(PhysicsObject* physics_object);
            void SimulatePhysics();
        private:
            static PhysicsEngine* instance_;
    };

    class PhysicsObject
    {
        public:
            PhysicsObject();
            virtual ~PhysicsObject(){};

            void Simulate();

            void SetPosition(glm::vec3 position);
            glm::vec3 GetPosition();

            void SetVelocity(glm::vec3 velocity);
            glm::vec3 GetVelocity();

            void ApplyForce(float x_force, float y_force, float z_force);
            void Stop();
        private:
            glm::vec3 position_;
            glm::vec3 velocity_;

            float mass_;
    };

}
#endif // PHYSICSENGINE_H
