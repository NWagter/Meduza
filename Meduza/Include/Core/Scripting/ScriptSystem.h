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
                void OnUpdate(float) override;

        };
    }
}