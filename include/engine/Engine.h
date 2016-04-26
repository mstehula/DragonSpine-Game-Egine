#ifndef ENGINE_H
#define ENGINE_H

#include "engine/EngineObject.h"
#include "systems/WindowSystem.h"
#include "systems/GraphicsSystem.h"
#include "systems/ObjectSystem.h"

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

            systems::ObjectSystem object_system_;
            systems::GraphicsSystem graphics_system_;
            systems::WindowSystem window_input_system_;

            void Run();
    };
}

#endif // ENGINE_H
