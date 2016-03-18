#ifndef SHADERS_H
#define SHADERS_H

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
        private:
            void AddProgram(const char* shader_filename, GLenum type);

            GLuint program_;
    };

}

#endif // SHADERS_H
