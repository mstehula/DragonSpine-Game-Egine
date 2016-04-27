#include <stdlib.h>
#include <stdio.h>

#include <vector>

#include "engine/Engine.h"
#include "engine/EngineObject.h"

#include "systems/ObjectSystem.h"
#include "systems/components/Components.h"

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

        engine::EngineObject engine_object;
        struct components::PositionComponent position_component;
        struct components::MotionComponent motion_component;
        struct components::MeshComponent mesh_component;

        engine_object.ID = 100000;
        objects_.Add(engine_object);

        position_component.position = glm::vec3(0.0,0.0,0.0);
        position_component.rotation = glm::vec3(0.0,0.5,0.0);
        positions_.Add(position_component);

        motion_component.linear_velocity = glm::vec3(0.0, .5, 0.0);
        motion_component.linear_acceleration = glm::vec3(0.0, -.1, 0.0);
        motion_component.rotational_velocity = glm::vec3(0.0, 1.0, 0.0);
        motion_.Add(motion_component);

        mesh_component.vertex_buffer_size = sizeof(vertex_buffer_data);
        glGenBuffers(1, &mesh_component.vertex_buffer_object);
        glBindBuffer(GL_ARRAY_BUFFER, mesh_component.vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, mesh_component.vertex_buffer_size, vertex_buffer_data, GL_STATIC_DRAW);

        mesh_component.index_buffer_size = sizeof(index_buffer_data);
        glGenBuffers(1, &mesh_component.index_buffer_object);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_component.index_buffer_object);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_component.index_buffer_size, index_buffer_data, GL_STATIC_DRAW);

        meshes_.Add(mesh_component);
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

    void ObjectSystem::CreateComponent(const char* object_name, const char* file_name)
    {

    }

    void ObjectSystem::DestroyObject(unsigned int object_id)
    {

    }

}
