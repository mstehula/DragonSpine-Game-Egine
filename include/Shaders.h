#ifndef SHADERS_H
#define SHADERS_H

#include <GLM/mat4x4.hpp>

namespace dragonspinegameengine
{

    class Shader
    {
        public:
            Shader();

            void Bind();
            void CompileShader();

            void AddVertexShader(const char* shader_filename);
            void AddGeometryShader(const char* shader_filename);
            void AddFragmentShader(const char* shader_filename);

            void AddBasicUniforms();

            void SetModelMatrix(glm::mat4x4 model_matrix);
            void SetViewMatrix(glm::mat4x4 world_matrix);
            void SetPerspectiveMatrix(glm::mat4x4 perspective_matrix);
        private:
            void AddProgram(const char* shader_filename, GLenum type);
            void LoadShader(const char* shader_filename, char** shader_file, int* shader_file_size);
            GLuint program_;
    };

}

#endif // SHADERS_H
