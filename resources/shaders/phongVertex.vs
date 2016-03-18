#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texPos;
layout (location = 2) in vec3 normal;

out vec2 texPos_;
out vec3 normal_;

uniform mat4 transform;

void main()
{
  gl_Position = transform * vec4(position, 1);
  texPos_ = texPos;
  normal_ = normal;
}
