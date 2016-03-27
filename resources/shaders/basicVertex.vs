#version 330

layout (location = 0) in vec4 position;

uniform mat4 model_matrix = mat4(1.0f);
uniform mat4 world_matrix = mat4(1.0f);
uniform mat4 perspective_matrix = mat4(1.0f);

out vec4 color_;

void main()
{
    color_ = position;
    gl_Position = perspective_matrix * world_matrix * model_matrix * position;
}
