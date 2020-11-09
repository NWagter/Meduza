#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{
    class RenderSystem : public BaseSystem
    {
        public:
        RenderSystem();
        
        protected:
        void Update(float) override;
        
    };
}