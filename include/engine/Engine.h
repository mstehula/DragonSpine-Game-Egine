#ifndef ENGINE_H
#define ENGINE_H

#include "engine/EngineObject.h"
#include "systems/WindowSystem.h"
#include "systems/ObjectSystem.h"
#include "systems/PhysicsSystem.hpp"
#include "systems/GraphicsSystem.h"

namespace engine
{
    class Engine
    {
        public:
            Engine();
            virtual ~Engine();

            void Init();
            void Start();
            void Tick(float dt);
            void Render(float dt);
            void Stop();

        private:
            bool running_;

            systems::WindowSystem window_input_system_;
            systems::ObjectSystem object_system_;
            systems::PhysicsSystem physics_system_;
            systems::GraphicsSystem graphics_system_;

            void Run();
    };
}

#endif // ENGINE_H
