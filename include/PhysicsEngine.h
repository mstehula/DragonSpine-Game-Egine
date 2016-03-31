#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <glm/vec3.hpp>

namespace dragonspinegameengine
{

    class PhysicsObject;

    class PhysicsEngine
    {
        public:
            static PhysicsEngine* GetInstance();

            void Simulate(PhysicsObject* physics_object);
        private:
            static PhysicsEngine* instance_;

            PhysicsEngine();
    };

    class PhysicsObject
    {
        public:
            void Simulate();

            void ApplyForce(float x_force, float y_force, float z_force);
            void ApplyForceDir(float front_froce, float side_force, float up_force);
            void Stop();
        private:
            glm::vec3 position_;
            glm::vec3 velocity_;
            glm::vec3 direction_;

            float mass_;
    };

}
#endif // PHYSICSENGINE_H
