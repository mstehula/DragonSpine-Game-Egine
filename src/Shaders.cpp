
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/mat4x4.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "engine\Engine.h"
#include "Shaders.h"

namespace dragonspinegameengine
{

    Shader::Shader()
    {
        program_ = glCreateProgram();

        if(program_ == 0)
        {
            engine::error("Shader creation failed");
            exit(1);
        }
    }

    void Shader::Bind()
    {
        glUseProgram(program_);
    }

    void Shader::CompileShader()
    {
        GLint function_return_value;
        glLinkProgram(program_);
        glGetProgramiv(program_, GL_LINK_STATUS, &function_return_value);
        if(function_return_value == GL_FALSE)
        {
            int error_buffer_size = 1024;
            char error_buffer[error_buffer_size];
            glGetProgramInfoLog(program_, error_buffer_size, &error_buffer_size, &error_buffer[0]);
            engine::error(error_buffer);
            exit(EXIT_FAILURE);
        }

        glValidateProgram(program_);
        glGetProgramiv(program_, GL_VALIDATE_STATUS, &function_return_value);
        if(function_return_value == GL_FALSE)
        {
            int error_buffer_size = 1024;
            char error_buffer[error_buffer_size];
            glGetProgramInfoLog(program_, error_buffer_size, &error_buffer_size, &error_buffer[0]);
            engine::error(error_buffer);
            exit(EXIT_FAILURE);
        }

        GLuint shaders[20];
        GLsizei count;
        glGetAttachedShaders(program_, 20, &count, shaders);
        for(int i = 0; i < count; i++)
        {
            glDetachShader(program_, shaders[i]);
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

    void Shader::SetModelMatrix(glm::mat4x4 model_matrix)
    {
        GLuint model_matrix_location = glGetUniformLocation(program_, "model_matrix");
        if(model_matrix_location == 0xFFFFFFFF)
        {
            engine::error("Could not find uniform: model matrix %d", model_matrix_location);
            exit(EXIT_FAILURE);
        }

        glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(model_matrix));
    }

    void Shader::SetViewMatrix(glm::mat4x4 world_matrix)
    {
        GLuint view_matrix_location = glGetUniformLocation(program_, "world_matrix");
        if(view_matrix_location == 0xFFFFFFFF)
        {
            engine::error("Could not find uniform: view matrix");
            exit(EXIT_FAILURE);
        }

        glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(world_matrix));
    }

    void Shader::SetPerspectiveMatrix(glm::mat4x4 perspective_matrix)
    {
        GLuint perspective_matrix_location = glGetUniformLocation(program_, "perspective_matrix");
        if(perspective_matrix_location == 0xFFFFFFFFF)
        {
            engine::error("Could not find uniform: perspective matrix");
            exit(EXIT_FAILURE);
        }

        glUniformMatrix4fv(perspective_matrix_location, 1, GL_FALSE, glm::value_ptr(perspective_matrix));
    }

    void Shader::AddProgram(const char* shader_filename, GLenum type)
    {
        GLint function_return_value;
        GLuint shader = glCreateShader(type);
        char* shader_file;
        int shader_file_size;
        LoadShader(shader_filename, &shader_file, &shader_file_size);

        if(shader == GL_FALSE)
        {
            engine::error("Shader creation failed\n");
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
            engine::error(error_buffer);
            exit(EXIT_FAILURE);
        }

        glAttachShader(program_, shader);
    }

    void Shader::LoadShader(const char* shader_filename, char** shader_file, int* shader_file_size)
    {
        engine::debug(engine::k_debug_all_, "Opening shader file: %s", shader_filename);
        FILE* shader = fopen(shader_filename, "r");
        if(shader == nullptr)
        {
            engine::error("Cannot open file for shader: %s", shader_filename);
            exit(1);
        }

        fseek(shader, 0, SEEK_END);
        *shader_file_size = ftell(shader);
        rewind(shader);

        *shader_file = (char*) malloc(*shader_file_size * sizeof(char));
        if(*shader_file == nullptr)
        {
            engine::error("malloc failed");
            exit(EXIT_FAILURE);
        }

        fread(*shader_file, sizeof(char), *shader_file_size, shader);

        fclose(shader);
    }

}
