#pragma once

namespace Me
{
    namespace Renderer
    {
        class ContextBase
        {
            public:
            ContextBase();
            virtual ~ContextBase();
            
            virtual void Resize(float,float) = 0;
        };
    }
}