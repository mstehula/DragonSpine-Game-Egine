#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include "engine\Engine.h"
#include "engine\EngineObject.h"

#include "systems\messages\GameMessage.h"
#include "systems\components\Components.h"
#include "systems\ISystem.h"

#include "util\DODArray.h"

namespace systems
{
    typedef util::DODArray<engine::EngineObject> EngineArray;
    typedef util::DODArray<components::PositionComponent> PositionArray;
    typedef util::DODArray<components::MotionComponent> MotionArray;
    typedef util::DODArray<components::MeshComponent> MeshArray;

    class ObjectSystem : public ISystem
    {
        public:
            void Init();
            void Update(float dt, ObjectSystem& factory);
            void SendMessageSync(messages::GameMessage* msg);
            void SendMessageAsync(messages::GameMessage* msg);
            virtual ~ObjectSystem(){}

            EngineArray& GetObjects() { return objects_; }
            PositionArray& GetPositions() { return positions_; }
            MotionArray& GetPhysics() { return physics_; }
            MeshArray& GetMeshes() { return mesh_; }
        private:
            EngineArray objects_;

            PositionArray positions_;
            MeshArray mesh_;
            MotionArray physics_;

            void CreateObject();
            void CreateComponent(const char* object_name, const char* file_name);
            void DestroyObject(unsigned int object_id);
    };
}

#endif // GAMEOBJECTFACTORY_H