
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine.h"
#include "Renderer.h"

using namespace dragonspinegameengine;

namespace dragonspinegameengine {

    int entry(int argc, char** argv)
    {
        debug(kDebugCritical, "Welcome to the DragonSpine Game Engine");
        debug(kDebugAll, "Starting...");

        Engine::GetInstance()->start();
        Engine::GetInstance()->exit();
        delete Engine::GetInstance();

        debug(kDebugAll, "Engine spinning down");
        debug(kDebugCritical, "Thank you for using the DragonSpine Game Engine");

        glfwTerminate();

        return 0;
    }

    Engine* Engine::instance_ = 0;
    Shader* Engine::shader_ = 0;

    Engine* Engine::GetInstance()
    {
        if(Engine::instance_ == nullptr)
        {
            Engine::instance_ = new Engine();
        }
        return instance_;
    }

    Shader* Engine::GetBasicShader()
    {
        if(Engine::shader_ == nullptr)
        {
            Engine::shader_ = new Shader();
        }
        return shader_;
    }

    void Engine::start()
    //To prevent starting again, use a boolean switch that
    //only starts the engine if it is not running
    {
        if(running) return;
        running = true;

        run();
    }

    void Engine::stop()
    {
        if(!running) return;
        running = false;
    }

    float rotation = 0;

    void Engine::run()
    {
        const int ticks_per_second = 100;
        const float game_skip_ticks = 1.0f/ticks_per_second;
        const float fps_skip_ticks = 1.0f;
        const int max_frame_skips = 5;

        double next_game_tick = getTime();
        double next_fps_tick = getTime();
        int loops;
        float interpolation;

        int frames = 0;
        int ticks = 0;

        renderer.InitWindow();

        GLfloat vertex_buffer_data1[] =
        {
            -1.0f,-1.0f,-1.0f, // triangle 1 : begin
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f,-1.0f, // triangle 2 : begin
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f, // triangle 2 : end
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
        };

        debug(3, "vertex buffer data size %d", sizeof(vertex_buffer_data1));

        obj1_ = new RenderableObject(glm::vec3(0.0,0.0,0.0), glm::vec3(0.0,0.0,0.0), glm::vec3(1,1,1));
        obj1_->GetMesh()->AddVertices(vertex_buffer_data1, sizeof(vertex_buffer_data1));

        GetBasicShader()->AddVertexShader("resources/shaders/basicVertex.vs");
        GetBasicShader()->AddFragmentShader("resources/shaders/basicFragment.fs");
        GetBasicShader()->CompileShader();
        GetBasicShader()->SetPerspectiveMatrix(glm::perspective(glm::radians(90.0f), (float) (1024 / 768), 0.1f, 100.0f));
        GetBasicShader()->SetViewMatrix(glm::lookAt(glm::vec3(40,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0)));

        while(running)
        {
            loops = 0;
            while(getTime() > next_game_tick && loops < max_frame_skips)
            {
                tick();
                ticks++;
                loops++;
                next_game_tick += game_skip_ticks;
            }

            if(getTime() > next_fps_tick)
            {
                debug(kDebugAll, "FPS:[%d] TPS:[%d]", frames, ticks);
                frames = 0;
                ticks = 0;
                next_fps_tick += fps_skip_ticks;
            }

            //Interpolation is how much of a second has passed by since the last render tick;
            interpolation = (float) ((getTime() + game_skip_ticks - next_game_tick) / game_skip_ticks);
            render();
            frames++;
        }
    }

    void Engine::tick()
    {
        rotation += .01;
        obj1_->SetRotation(glm::vec3(rotation, rotation, 0.0f));
        glfwPollEvents();
    }

    void Engine::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GetBasicShader()->Bind();
        GetBasicShader()->SetPerspectiveMatrix(glm::perspective(glm::radians(90.0f), (float) (1024 / 768), 0.1f, 100.0f));
        GetBasicShader()->SetViewMatrix(glm::lookAt(glm::vec3(4,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0)));
        obj1_->Render();
        renderer.Render();
    }

    void Engine::exit()
    {
        delete shader_;
        delete obj1_;
        delete obj2_;
    }

    void ResourceLoader::LoadShader(const char* shader_filename, char** shader_file, int* shader_file_size)
    {
        debug(3, "Opening shader file: %s", shader_filename);
        FILE* shader = fopen(shader_filename, "r");
        if(shader == nullptr)
        {
            error("Cannot open file for shader: %s", shader_filename);
            exit(1);
        }

        fseek(shader, 0, SEEK_END);
        *shader_file_size = ftell(shader);
        rewind(shader);

        *shader_file = (char*) malloc(*shader_file_size * sizeof(char));
        if(*shader_file == nullptr)
        {
            error("malloc failed");
            exit(EXIT_FAILURE);
        }

        fread(*shader_file, sizeof(char), *shader_file_size, shader);

        fclose(shader);
    }

    //Returns the time since the start of glfw or since int in setTime(int)
    double getTime()
    {
        return glfwGetTime();
    }

    //Holds the value of the debug level. Consists of 4 levels
    // - 1: Prints only the critical warning or errors
    // - 2: Prints out any other warnings not covered by 1
    // - 3: Prints out things that the developers should know
    // - 4: Prints out all debugging values
    int game_debug_level = kDebugAll;

    //Prints out char* output if debug_level is less then the current
    //game debug_level
    void debug(int debug_level, const char * format, ...)
    {
        if(debug_level <= game_debug_level)
        {
            va_list argptr;
            va_start(argptr, format);
            fprintf(stdout, "[%c][%f] ", kDebugSymbolTable[debug_level], getTime());
            vfprintf(stdout, format, argptr);
            fprintf(stdout, "\n");
            va_end(argptr);
        }
    }

    //Prints out the char* output to stderr
    void error(const char* format, ...)
    {
        va_list argptr;
        va_start(argptr, format);
        fprintf(stdout, "[E][%f] ", getTime());
        vfprintf(stdout, format, argptr);
        fprintf(stdout, "\n");
        va_end(argptr);
    }

    //Sets debug level of the program - changed most notibly in the command line
    void setDebugLevel(int debug_level)
    {
        game_debug_level = debug_level;
    }

}
