#ifndef ENGINE_H
#define ENGINE_H

#include <glm/vec3.hpp>

namespace dragonspinegameengine
{
    class EngineObject
    {
    public:
        EngineObject(){};
        virtual ~EngineObject(){}
    private:
        glm::vec3 position_;
        glm::vec3 velocity_;
    };
}

#include "GraphicsEngine.h"
#include "InputEngine.h"
#include "PhysicsEngine.h"

namespace dragonspinegameengine {

    int entry(int argc, char** argv);

    class Engine
    {
        public:
            struct EngineConfig
            {
                int ticks_per_second_ = 1;
                int max_frame_skips_ = 1;

                bool physics_engine_ = false;
                bool graphics_engine_ = true;
            };

            static Engine* GetEngine();

            void ConfigureEngine(struct EngineConfig config);
            struct EngineConfig GetConfig();

            void Start();
            void Stop();

            void RegisterObect(EngineObject* object);
            void UnregisterObject(EngineObject* object);
        private:
            static Engine* engine_;
            GraphicsEngine* graphics_engine_;
            PhysicsEngine* physics_engine_;
            InputEngine* input_engine_;

            EngineConfig config_;

            bool running_ = false;

            void Run();
    };

    class ResourceLoader
    {
        public:
            static void LoadShader(const char* shader_filename, char** shader_file, int* shader_file_size);
    };

    double getTime();

    const int kDebugCritical = 0;
    const int kDebugWarning = 1;
    const int kDebugAdvisory = 2;
    const int kDebugAll = 3;

    const char kDebugSymbolTable[] = {'!', 'W', 'A', '='};

    void debug(int debug_level, const char* format, ...);
    void error(const char* format, ...);

    void setDebugLevel(int debug_level);
}

#endif // ENGINE_H
