#version 330

layout (location = 0) in vec4 position;

uniform mat4x4 model_matrix = mat4x4(1.0f);
uniform mat4x4 world_matrix = mat4x4(1.0f);
uniform mat4x4 perspective_matrix = mat4x4(1.0f);

out vec4 color;

void main()
{
    color = clamp(position, 0.0f, 1.0f);
    gl_Position = perspective_matrix * world_matrix * model_matrix * position;
}
