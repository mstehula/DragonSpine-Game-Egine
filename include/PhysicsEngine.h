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
<<<<<<< HEAD

            void SetPosition(glm::vec3 position);
            glm::vec3 GetPosition();

            void SetVelocity(glm::vec3 velocity);
            glm::vec3 GetVelocity();

            void ApplyForce(float x_force, float y_force, float z_force);
=======

            void ApplyForce(float x_force, float y_force, float z_force);
            void ApplyForceDir(float front_froce, float side_force, float up_force);
>>>>>>> 030ad8506f6c2c8351350b15f4679771f893177a
            void Stop();
        private:
            glm::vec3 position_;
            glm::vec3 velocity_;
<<<<<<< HEAD
=======
            glm::vec3 direction_;
>>>>>>> 030ad8506f6c2c8351350b15f4679771f893177a

            float mass_;
    };

}
#endif // PHYSICSENGINE_H
