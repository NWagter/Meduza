#pragma once

#include "EntityTypes.h"

namespace Me
{
    struct BaseComponent
    {
        virtual void Reset(){}
        static ComponentID s_componentID;
    };


    struct TagComponent : public BaseComponent
    {
        std::string m_tag;
        
        static ComponentID s_componentID;
    };
    
    struct EditorComponent : public BaseComponent
    {        
        static ComponentID s_componentID;
    };
}