#ifndef GRAPHICS_SYSTEM_H
#define GRAPHICS_SYSTEM_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/mat4x4.hpp"

#include "systems/ISystem.h"
#include "systems/messages/GameMessage.h"

namespace systems
{
    class GraphicsSystem : public ISystem
    {
        public:
            void Init();
            void Update(float dt, ObjectSystem& factory);
            void SendMessageSync(messages::GameMessage* msg);
            void SendMessageAsync(messages::GameMessage* msg);
            virtual ~GraphicsSystem(){}
        protected:

        private:
            GLFWwindow* window_;

            GLuint program_;

            void AddVertexShader(const char* file_name);
            void AddFragmentShader(const char* file_name);
            void AddGeometryShader(const char* file_name);
            void AddShader(const char* file_name, GLenum type);
            void CompileShader();

            void SetModelMatrix(glm::mat4x4 model_matrix);
            void SetWorldMatrix(glm::mat4x4 world_matrix);
            void SetPerspectiveMatrix(glm::mat4x4 perspective_matrix);
    };
}
#endif // GRAPHICS_H
