#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    struct TransformComponent;
    struct CameraComponent;

    namespace Editor
    {
        class EditorCameraSystem : public BaseSystem<EditorComponent, TransformComponent, CameraComponent>
        {
            public:
                EditorCameraSystem();
                ~EditorCameraSystem();

            protected:
                void OnCreate() override;  
                void OnUpdate(float) override;  

            private:
        };
    }
}