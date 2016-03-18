#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Engine.h"
#include "Shaders.h"

namespace dragonspinegameengine
{

    Shader::Shader()
    {
        program_ = glCreateProgram();

        if(program_ == 0)
        {
            error("Shader creation failed");
            exit(1);
        }
    }

    void Shader::AddVertexShader(const char* shader_filename)
    {
        AddProgram(shader_filename, GL_VERTEX_SHADER);
    }

    void Shader::AddGeometryShader(const char* shader_filename)
    {
        AddProgram(shader_filename, GL_GEOMETRY_SHADER);
    }

    void Shader::AddFragmentShader(const char* shader_filename)
    {
        AddProgram(shader_filename, GL_FRAGMENT_SHADER);
    }

    void Shader::AddProgram(const char* shader_filename, GLenum type)
    {
        GLint function_return_value;
        GLuint shader = glCreateShader(type);
        char* shader_file;
        int shader_file_size;
        ResourceLoader::LoadShader(shader_filename, &shader_file, &shader_file_size);

        if(shader == GL_FALSE)
        {
            error("Shader creation failed\n");
            exit(EXIT_FAILURE);
        }
        glShaderSource(shader, 1, &shader_file, &shader_file_size);
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &function_return_value);
        if(function_return_value == GL_FALSE)
        {
            int error_buffer_size = 1024;
            char error_buffer[error_buffer_size];
            glGetShaderInfoLog(shader, error_buffer_size, &error_buffer_size, error_buffer);
            error(error_buffer);
            exit(EXIT_FAILURE);
        }

        glAttachShader(program_, shader);

        glLinkProgram(program_);
        glGetProgramiv(program_, GL_LINK_STATUS, &function_return_value);
        if(function_return_value == GL_FALSE)
        {
            int error_buffer_size = 1024;
            char error_buffer[error_buffer_size];
            glGetProgramInfoLog(program_, error_buffer_size, &error_buffer_size, &error_buffer[0]);
            error(error_buffer);
            exit(EXIT_FAILURE);
        }

        glValidateProgram(program_);
        glGetProgramiv(program_, GL_VALIDATE_STATUS, &function_return_value);
        if(function_return_value == GL_FALSE)
        {
            int error_buffer_size = 1024;
            char error_buffer[error_buffer_size];
            glGetProgramInfoLog(program_, error_buffer_size, &error_buffer_size, &error_buffer[0]);
            error(error_buffer);
            exit(EXIT_FAILURE);
        }

        glDetachShader(program_, shader);

        glDeleteShader(shader);
    }

    void Shader::Bind()
    {
        glUseProgram(program_);
    }


}
