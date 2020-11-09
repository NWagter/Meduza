#pragma once

#include "EntityTypes.h"

namespace Me
{
    struct BaseComponent
    {
        virtual ComponentID GetComponentID() = 0;
    };
    
}