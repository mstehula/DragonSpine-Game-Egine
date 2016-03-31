#ifndef ENGINE_H
#define ENGINE_H

#include "GraphicsEngine.h"
#include "Shaders.h"

namespace dragonspinegameengine {

    int entry(int argc, char** argv);

    class Engine
    {
        public:
            static Engine* GetInstance();
            static Shader* GetBasicShader();
            static GraphicsEngine* GetGraphicsEngine();

            void start();
            void stop();

            void tick();
            void render();

            void exit();
        protected:

        private:
            static Engine* instance_;
            static Shader* shader_;
            static GraphicsEngine* graphics_engine_;

            RenderableObject* obj1_;
            RenderableObject* obj2_;

            bool running = false;
            void run();
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
