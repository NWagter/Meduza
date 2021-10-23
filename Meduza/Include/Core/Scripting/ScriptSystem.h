#pragma once

#include "ECS/BaseSystem.h"
#include "Core/Scripting/ScriptComponent.h"

namespace Me
{
    namespace Scripting
    {
        class ScriptSystem : public BaseSystem<ScriptComponent>
        {
            public:
                ScriptSystem();
                ~ScriptSystem();

            protected:
                void OnStart() override;
                void OnUpdate(float) override;

                void Start(ScriptComponent*, EntityID);

        };
    }
}