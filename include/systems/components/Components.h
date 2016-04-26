#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <GL/glew.h>

#include "glm/vec3.hpp"

namespace components
{
    enum ComponentMask
    {
        COMPONENT_NONE = 0,
        COMPONENT_POSITION = 1 << 0,
        COMPONENT_MOTION = 1 << 1,
        COMPONENT_COLLISION = 1 << 2,
        COMPONENT_MESH = 1 << 3
    };

    /**
    * Positional Component: Any object that has a position
    *   also has a positional component
    * - position: Holds the x, y, and z component for
    *   for the object
    * - rotation: Holds the rotation in rx, ry and rz for
    *   roll, pitch and yaw (some variation of ordering)
    * - scale: Holds the scale component for the object
    **/
    struct PositionComponent
    {
        glm::vec3 position;
        glm::vec3 rotation;
        float scale;
    };

    struct MotionComponent
    {
        glm::vec3 linear_velocity;
        glm::vec3 linear_acceleration;
        glm::vec3 rotational_velocity;
        glm::vec3 rotational_acceleration;
    };

    struct CollisionComponent
    {

    };

    struct MeshComponent
    {
        GLuint vertex_buffer_object;
        GLuint vertex_buffer_size;
        GLuint index_buffer_object;
        GLuint index_buffer_size;
    };
}

#endif // COMPONENTS_H
