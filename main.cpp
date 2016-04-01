
#include "Engine.h"
#include "main.h"

using namespace dragonspinegameengine;

int main(int argc, char** argv)
{
    struct Engine::EngineConfig config;
    config.ticks_per_second_ = 50;
    config.max_frame_skips_ = 10;
    config.graphics_engine_ = true;
    config.physics_engine_ = true;

    Engine::GetEngine()->ConfigureEngine(config);

    GLfloat vertex_buffer_data[] =
    {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f,-1.0f,
        1.0f, -1.0f,1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f, 1.0f,1.0f,
    };

    int index_buffer_data[] =
    {
        0,1,3,
        0,3,2,
        0,5,1,
        0,4,5,
        0,2,6,
        0,6,4,
        7,3,1,
        7,1,5,
        7,5,4,
        7,4,6,
        7,3,2,
        7,2,6
    };

    Entity entity;
    entity.GetMesh()->AddVertices(vertex_buffer_data, sizeof(vertex_buffer_data), index_buffer_data, sizeof(index_buffer_data));

    Engine::GetEngine()->Start();
}
