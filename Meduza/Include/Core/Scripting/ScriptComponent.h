#pragma once

#include "ECS/BaseComponent.h"
#include "ECS/EntityTypes.h"

namespace Me
{    
    namespace Scripting
    {
        struct ScriptComponent : BaseComponent
        { 
            std::string m_script;

            static ComponentID s_componentID;
        };
    }
}