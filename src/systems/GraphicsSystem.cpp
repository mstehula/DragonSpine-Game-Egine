#include <stdio.h>
#include <stdlib.h>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

#include "engine/Engine.h"

#include "systems/ObjectSystem.h"
#include "systems/GraphicsSystem.h"
#include "systems/components/Components.h"
#include "systems/messages/GameMessage.h"

namespace systems
{
    void GraphicsSystem::Init()
    {
        window_ = glfwGetCurrentContext();
        glfwShowWindow(window_);

        program_ = glCreateProgram();
        AddVertexShader("resources/shaders/basicVertex.vs");
        AddFragmentShader("resources/shaders/basicFragment.fs");

        CompileShader();
    }

    void GraphicsSystem::Update(float dt, ObjectSystem& factory)
    {
        EngineArray& objects = factory.GetObjects();
        PositionArray& position = factory.GetPositions();
        MotionArray& physics = factory.GetPhysics();
        MeshArray& meshes = factory.GetMeshes();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program_);

        SetPerspectiveMatrix(glm::perspective((float) 45,(float) 800/600,(float) .1,(float) 100));
        SetWorldMatrix(glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));

        for(unsigned int i = 0; i < objects.Size(); i++)
        {
            SetModelMatrix(glm::translate(position[i].position));

            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER,meshes[i].vertex_buffer_object);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshes[i].index_buffer_object);
            glDrawElements(GL_TRIANGLES, meshes[i].index_buffer_size, GL_UNSIGNED_INT, 0);

            glDisableVertexAttribArray(0);
        }

        if(glfwWindowShouldClose(window_))
        {
            glfwTerminate();
            return;
        }

        glfwSwapBuffers(window_);
    }

    void GraphicsSystem::SendMessageSync(messages::GameMessage* msg)
    {
        switch(msg->id)
        {
        case 10:
            this->window_ = glfwGetCurrentContext();
            break;
        default:
            break;
        }
    }

    void GraphicsSystem::SendMessageAsync(messages::GameMessage* msg)
    {

    }

    void GraphicsSystem::AddVertexShader(const char* file_name)
    {
        AddShader(file_name, GL_VERTEX_SHADER);
    }

    void GraphicsSystem::AddFragmentShader(const char* file_name)
    {
        AddShader(file_name, GL_FRAGMENT_SHADER);
    }

    void GraphicsSystem::AddGeometryShader(const char* file_name)
    {
        AddShader(file_name, GL_GEOMETRY_SHADER);
    }

    void GraphicsSystem::AddShader(const char* file_name, GLenum type)
    {
        GLint function_return_value;
        GLuint shader = glCreateShader(type);
        char* shader_array;
        int shader_array_size;

        FILE* shader_file = fopen(file_name, "r");
        if(shader_file == NULL)
        {
            exit(1);
        }

        fseek(shader_file, 0, SEEK_END);
        shader_array_size = ftell(shader_file);
        rewind(shader_file);

        shader_array = (char*) malloc(shader_array_size * sizeof(char));
        if(shader_array == NULL)
        {
            exit(EXIT_FAILURE);
        }

        fread(shader_array, sizeof(char), shader_array_size, shader_file);

        fclose(shader_file);

        if(shader == GL_FALSE)
        {
            exit(EXIT_FAILURE);
        }
        glShaderSource(shader, 1, &shader_array, &shader_array_size);
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &function_return_value);
        if(function_return_value == GL_FALSE)
        {
            int error_buffer_size = 1024;
            char error_buffer[error_buffer_size];
            glGetShaderInfoLog(shader, error_buffer_size, &error_buffer_size, error_buffer);
            exit(EXIT_FAILURE);
        }

        glAttachShader(program_, shader);
    }

    void GraphicsSystem::CompileShader()
    {
        GLint function_return_value;
        glLinkProgram(program_);
        glGetProgramiv(program_, GL_LINK_STATUS, &function_return_value);
        if(function_return_value == GL_FALSE)
        {
            int error_buffer_size = 1024;
            char error_buffer[error_buffer_size];
            glGetProgramInfoLog(program_, error_buffer_size, &error_buffer_size, &error_buffer[0]);
            exit(EXIT_FAILURE);
        }

        glValidateProgram(program_);
        glGetProgramiv(program_, GL_VALIDATE_STATUS, &function_return_value);
        if(function_return_value == GL_FALSE)
        {
            int error_buffer_size = 1024;
            char error_buffer[error_buffer_size];
            glGetProgramInfoLog(program_, error_buffer_size, &error_buffer_size, &error_buffer[0]);
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

    void GraphicsSystem::SetModelMatrix(glm::mat4x4 model_matrix)
    {
        GLuint model_matrix_location = glGetUniformLocation(program_, "model_matrix");
        if(model_matrix_location == 0xFFFFFFFF)
        {
            exit(EXIT_FAILURE);
        }

        glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(model_matrix));
    }

    void GraphicsSystem::SetWorldMatrix(glm::mat4x4 world_matrix)
    {
        GLuint view_matrix_location = glGetUniformLocation(program_, "world_matrix");
        if(view_matrix_location == 0xFFFFFFFF)
        {
            exit(EXIT_FAILURE);
        }

        glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(world_matrix));
    }

    void GraphicsSystem::SetPerspectiveMatrix(glm::mat4x4 perspective_matrix)
    {
        GLuint perspective_matrix_location = glGetUniformLocation(program_, "perspective_matrix");
        if(perspective_matrix_location == 0xFFFFFFFFF)
        {
            exit(EXIT_FAILURE);
        }

        glUniformMatrix4fv(perspective_matrix_location, 1, GL_FALSE, glm::value_ptr(perspective_matrix));
    }
}
