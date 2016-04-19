#ifndef ENGINE_H
#define ENGINE_H

namespace engine
{
    const int k_debug_critical_ = 0;
    const int k_debug_warning_ = 1;
    const int k_debug_advisory_ = 2;
    const int k_debug_all_ = 3;

    void debug(int debug_level, const char* format, ...);
    void error(const char* format, ...);

    void setDebugLevel(int debug_level);

    const char debug_symbol_table_[4] = {'!', 'W', 'A', '='};
}

#include "engine\EngineObject.h"
#include "systems\WindowSystem.h"
#include "systems\GraphicsSystem.h"
#include "systems\ObjectSystem.h"

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
            bool running_ = false;

            systems::ObjectSystem object_system_;
            systems::GraphicsSystem graphics_system_;
            systems::WindowSystem window_input_system_;

            void Run();
    };
}

#endif // ENGINE_H
