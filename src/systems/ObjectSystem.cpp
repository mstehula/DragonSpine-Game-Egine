#include <stdlib.h>
#include <stdio.h>

#include <vector>

#include "engine\Engine.h"
#include "engine\EngineObject.h"

#include "systems\ObjectSystem.h"

namespace systems
{
    void ObjectSystem::Init()
    {
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

        engine::debug(engine::k_debug_all_, "Setting Object ID");

        CreateObject();
        engine::debug(engine::k_debug_all_, "objects_[0].ID = %d", objects_[0].ID);
        objects_[0].ID = 100000;
        engine::debug(engine::k_debug_all_, "objects_[0].ID = %d", objects_[0].ID);
        engine::debug(engine::k_debug_all_, "objects size %d", objects_.Size());

        engine::debug(engine::k_debug_all_, "Loading vertex buffer");

        positions_[0].position = glm::vec3(0.0,2.0,0.0);

        mesh_[0].vertex_buffer_size = sizeof(vertex_buffer_data);
        glGenBuffers(1, &mesh_[0].vertex_buffer_object);
        glBindBuffer(GL_ARRAY_BUFFER, mesh_[0].vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, mesh_[0].vertex_buffer_size, vertex_buffer_data, GL_STATIC_DRAW);

        engine::debug(engine::k_debug_all_, "Loading index buffer");

        mesh_[0].index_buffer_size = sizeof(index_buffer_data);
        glGenBuffers(1, &mesh_[0].index_buffer_object);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_[0].index_buffer_object);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_[0].index_buffer_size, index_buffer_data, GL_STATIC_DRAW);

        engine::debug(engine::k_debug_all_, "Pushing mesh to buffer");
    }

    void ObjectSystem::Update(float dt, ObjectSystem& factory)
    {

    }

    void ObjectSystem::SendMessageSync(messages::GameMessage* msg)
    {

    }

    void ObjectSystem::SendMessageAsync(messages::GameMessage* msg)
    {

    }

    void ObjectSystem::CreateObject()
    {
        objects_.Add();
        positions_.Add();
        mesh_.Add();
        physics_.Add();
    }

    void ObjectSystem::CreateComponent(const char* object_name, const char* file_name)
    {

    }

    void ObjectSystem::DestroyObject(unsigned int object_id)
    {

    }

}
